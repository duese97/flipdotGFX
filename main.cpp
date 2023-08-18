#include <Arduino.h>
#include <math.h>
#include "flipdotGFX.h"

#define FLIPDOT_ROWS 19
#define FLIPDOT_COLS 28

#define LENGTH_SECONDS_HAND 7
#define LENGTH_MINUTE_HAND  5

#define CENTER_X_CLOCK 14
#define CENTER_Y_CLOCK 9

typedef struct
{
  int end_sec_x, end_sec_y;
  int end_min_x, end_min_y;
  int end_hour_x, end_hour_y;
} hand_pos_t;

hand_pos_t clock_state;

/* Small custom double point, since otherwise showing time would need too many
 * horizontal flipdots. */
static const char double_point_2x7[7][2] =
{
  {' ', ' '},
  {'X', 'X'},
  {'X', 'X'},
  {' ', ' '},
  {'X', 'X'},
  {'X', 'X'},
  {' ', ' '}
};

// setup double buffered frame
FLIPDOT_SETUP_BUFFER(frame_buf, FLIPDOT_ROWS, FLIPDOT_COLS);

// init HW UART object
HardwareSerial customSerial(0);

int sec_count, min_count;

/* Just a dummy */
bool write_dot_wrapper(int row, int col, char state)
{
  return true;
}

bool write_row_wrapper(int row, char* states)
{
  char printbuf[64];
  int size = snprintf(printbuf, sizeof(printbuf), "row:%ld: %.28s\n", row, states);
  customSerial.write(printbuf, size);

  return true;
}

bool write_col_wrapper(int col, char* states)
{
  char printbuf[64];
  int size = snprintf(printbuf, sizeof(printbuf), "col:%ld: %.19s\n", col, states);
  customSerial.write(printbuf, size);

  return true;
}

/* For debug prints */
int print_wrapper(char* buff, int len)
{
  int ret = customSerial.write(buff, len);
  return ret;
}

/* Calculate where the next hand position is */
void calc_hand_pos(int degrees, int length, int* new_x, int* new_y)
{
  // convert to radians
  float angle = (PI * 2 * degrees) / 360.0;

  // sin(angle) = new_x / length -> new_x = sin(angle) * length
  // cos(angle) = new_y / length -> new_y = cos(angle) * length
  *new_x = round(sin(angle) * length);
  *new_y = round(cos(angle) * length);
  
  // take into account that coordinates are
  // positive from left to right and top to down -> mirrored on y axis!
  (*new_y) = (*new_y) * -1;
}


void setup()
{
  customSerial.begin(115200, SERIAL_8N1, 36, 35); // use HW UART

  flipdot_hw_info_t config = {
    .rows           = FLIPDOT_ROWS,
    .columns        = FLIPDOT_COLS,
    .frame_buf      = &frame_buf[0][0],

    //.write_dot_cb     = write_dot_wrapper,
    //.write_column_cb  = write_col_wrapper,
    .write_row_cb     = write_row_wrapper,

    .print            = print_wrapper,
  };
  
  flipdot_gfx_init(&config);

  /* Briefly flash display */
  flipdot_gfx_fill(false, true);  // force clear
  flipdot_gfx_fill(true, true);   // force set

  /* Write inverted text */
  flipdot_gfx_set_printmode(true);
  flipdot_gfx_set_cursor(7, 2);
  flipdot_gfx_write_5x7_line((char*)"TEST");
  flipdot_gfx_write_framebuf();
  flipdot_gfx_set_printmode(false); // go back to normal mode

  flipdot_gfx_fill(false, true);  // force clear

  /* Write some random text for demonstration */
  flipdot_gfx_set_cursor(1, 0);
  flipdot_gfx_write_5x7_line((char*)"12");
  flipdot_gfx_write_bitmap(&double_point_2x7[0][0], 2, 7, true);
  flipdot_gfx_set_cursor_relative(0, 1);
  flipdot_gfx_write_5x7_line((char*)"39");
  flipdot_gfx_write_framebuf();

  flipdot_gfx_set_cursor(11, 0);
  flipdot_gfx_write_5x7_line((char*)"10%");
  flipdot_gfx_write_framebuf();

  flipdot_gfx_set_cursor(1, 0);
  flipdot_gfx_write_5x7_line((char*)"10:28");
  flipdot_gfx_write_framebuf();

  /* Draw some basic shapes for demonstration */
  flipdot_gfx_draw_line(0, 9, 27, 9);
  flipdot_gfx_write_framebuf();
}

/* Basic clock example */
void loop()
{
  bool first_run = true;

  /* Setup clock face */
  flipdot_gfx_fill(false, false);  // "soft clear"
  flipdot_gfx_draw_circle(CENTER_X_CLOCK, CENTER_Y_CLOCK, 9);
  flipdot_gfx_write_framebuf();

  while (1)
  {
    if (first_run)
    {
      first_run = false;
    }
    else // only when at least once calculated
    {
      /* Erase the old line */
      flipdot_gfx_set_printmode(true);
      flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, clock_state.end_sec_x, clock_state.end_sec_y);
      flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, clock_state.end_min_x, clock_state.end_min_y);
      //flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, clock_state.end_hour_x, clock_state.end_hour_y);
    }

    calc_hand_pos(sec_count * 6, LENGTH_SECONDS_HAND, &clock_state.end_sec_x, &clock_state.end_sec_y);
    clock_state.end_sec_x += CENTER_X_CLOCK;
    clock_state.end_sec_y += CENTER_Y_CLOCK;
  
    calc_hand_pos(min_count * 6, LENGTH_MINUTE_HAND, &clock_state.end_min_x, &clock_state.end_min_y);
    clock_state.end_min_x += CENTER_X_CLOCK;
    clock_state.end_min_y += CENTER_Y_CLOCK;
    
    /* Draw a new one in slightly different position */
    flipdot_gfx_set_printmode(false);
    flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, clock_state.end_sec_x, clock_state.end_sec_y);
    flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, clock_state.end_min_x, clock_state.end_min_y);
    flipdot_gfx_write_framebuf();

    delay(1000);
    sec_count++;
    if (sec_count >= 60)
    {
      sec_count = 0;
      min_count++;
      if (min_count >= 60)
      {
        min_count = 0;
      }
    }
  }
}
