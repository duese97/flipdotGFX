#include <Arduino.h>
#include <math.h>
#include "flipdotGFX.h"

#define FLIPDOT_ROWS 19
#define FLIPDOT_COLS 28

#define LENGTH_SECONDS_HAND 7
#define CENTER_X_CLOCK 14
#define CENTER_Y_CLOCK 9

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

// as a scratchpad and to hold image (meta) info
static char frame_buf[FLIPDOT_ROWS*FLIPDOT_COLS];

// init HW UART object
HardwareSerial customSerial(0);

int sec_count;

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

/* For debug prints */
int print_wrapper(char* buff, int len)
{
  int ret = customSerial.write(buff, len);
  return ret;
}

/* Calculate where the next hand position is */
void calc_hand_pos(int seconds, int length, int* new_x, int* new_y)
{
  // convert to angle (0s -> 0°, 60s -> 360*) and then to radians
  float angle = (float)(seconds * 6 * 2 * PI) / 360.0;

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
    .rows       = FLIPDOT_ROWS,
    .columns    = FLIPDOT_COLS,
    .frame_buf  = frame_buf,

    .write_dot_cb     = NULL, //write_dot_wrapper,
    .write_column_cb  = NULL,
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
  int end_x = 0, end_y = 0;

  /* Setup clock face */
  flipdot_gfx_fill(false, false);  // "soft clear"
  flipdot_gfx_draw_circle(CENTER_X_CLOCK, CENTER_Y_CLOCK, 9);
  flipdot_gfx_write_framebuf();

  while (1)
  {
    if (end_x && end_y) // only when at least once calculated
    {
      /* Erase the old line */
      flipdot_gfx_set_printmode(true);
      flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, end_x, end_y);
    }

    calc_hand_pos(sec_count, LENGTH_SECONDS_HAND, &end_x, &end_y);
    end_x += CENTER_X_CLOCK;
    end_y += CENTER_Y_CLOCK;
    
    /* Draw a new one in slightly different position */
    flipdot_gfx_set_printmode(false);
    flipdot_gfx_draw_line(CENTER_X_CLOCK, CENTER_Y_CLOCK, end_x, end_y);
    flipdot_gfx_write_framebuf();

    delay(1000);
    sec_count++;
    if (sec_count >= 60)
    {
      sec_count = 0;
    }
  }
}
