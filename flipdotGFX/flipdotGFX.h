#ifndef _FLIPDOT_GFX_H_
#define _FLIPDOT_GFX_H_

#include <stdbool.h>


//************************************************************************
// Exported macros and enums
//************************************************************************
#define FLIPDOT_SETUP_BUFFER(name,rows,cols) static char name[rows*2][(cols+0x7)/8]

typedef enum
{
    FLIPDOT_SET         = 'X', // steady state set
    FLIPDOT_RESET       = ' ', // steady state reset

    /* Meta states */
    FLIPDOT_NEW_SET     = 'S', // to be flipped from reset -> set
    FLIPDOT_NEW_RESET   = 'R', // to be flipped from set -> reset
} flipdot_states_t;


//************************************************************************
// Exported types
//************************************************************************
typedef struct
{
    int rows; // number of available rows
    int columns; // number of available columns

    /* Hold current state of flipdot and for use as scratchpad.
     * Must be 2 * x * y bytes in size, where:
     *  x number of rows
     *  y number of columns / 8 and rounded up to the next higher integer */
    char* frame_buf;

    /* hw abstraction, */
    bool (*write_dot_cb)(int row, int col, char state);
    bool (*write_column_cb)(int col, char* states);
    bool (*write_row_cb)(int row, char* states);

    int (*print)(char *buffer, int len);
} flipdot_hw_info_t;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//************************************************************************
// Exported functions
//************************************************************************
// config
bool flipdot_gfx_init(flipdot_hw_info_t* ptr);
void flipdot_gfx_set_printmode(bool new_mode);

// writing and clearing
bool flipdot_gfx_fill(bool state, bool force);
bool flipdot_gfx_write_framebuf(void);

// text and bitmap stuff
void flipdot_gfx_set_cursor(int row, int col);
void flipdot_gfx_set_cursor_relative(int row, int col);
void flipdot_gfx_write_5x7_line(char* format);
bool flipdot_gfx_shift_5x7_line(char* format, int shift_step, bool first_shift);
bool flipdot_gfx_write_bitmap(const char* bitmap, int len_x, int len_y, bool move_cursor);

// basic shapes
void flipdot_gfx_draw_point(int x, int y);
void flipdot_gfx_draw_circle(int x0, int y0, int r);
void flipdot_gfx_draw_line(int x0, int y0, int x1, int y1);

// debug
void flipdot_gfx_dbg_print_framebuf(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FLIPDOT_GFX_H_
