#ifndef _FLIPDOT_GFX_H_
#define _FLIPDOT_GFX_H_

#include <stdbool.h>

typedef enum
{
    FLIPDOT_SET         = 'X', // steady state set
    FLIPDOT_RESET       = ' ', // steady state reset

    /* Meta states */
    FLIPDOT_NEW_SET     = 'S', // to be flipped from reset -> set
    FLIPDOT_NEW_RESET   = 'R', // to be flipped from set -> reset
} flipdot_states_t;

typedef struct
{
    int rows; // number of available rows
    int columns; // number of available columns

    // hold current state of flipdot and for use as scratchpad, pointer to buffer which is rows x columns sized
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

bool flipdot_gfx_init(flipdot_hw_info_t* ptr);

bool flipdot_gfx_fill(bool state, bool force);

void flipdot_gfx_set_cursor(int row, int col);
void flipdot_gfx_set_cursor_relative(int row, int col);
void flipdot_gfx_dbg_print_framebuf(void);
void flipdot_gfx_write_5x7_line(char* format);
void flipdot_gfx_write_bitmap(const char* bitmap, int len_x, int len_y, bool move_cursor);
void flipdot_gfx_draw_line(int x0, int y0, int x1, int y1);

bool flipdot_gfx_write_framebuf(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _FLIPDOT_GFX_H_
