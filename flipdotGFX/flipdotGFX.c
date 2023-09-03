#include <stddef.h>
#include <string.h> // for memset,..

#include <flipdotGFX.h>
#include <characterROM.h>


//************************************************************************
// Local macros
//************************************************************************
#define SGN(_x)         ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

//************************************************************************
// Local variables
//************************************************************************
static flipdot_hw_info_t hw_info;   // local copy of given HW info struct

// current printing position
static int curr_cursor_x;
static int curr_cursor_y;

// to avoid having to calculate number of column bytes over and over
static int num_col_bytes;

// to avoid calculating over and over length of framebuf
static int num_framebuf_bytes;

// if true, drawing will be be inverted
static bool print_inverted = false;

static char* scratchpad;
static char* curr_state;

//************************************************************************
// Local functions/helpers declarations
//************************************************************************
static inline flipdot_states_t flipdot_gfx_cmp_bits(bool old, bool new);
static inline bool flipdot_gfx_get_bit(int row, int col, char* framebuf);


//************************************************************************
// Exported functions
//************************************************************************

/** @brief Init this library
 *  @details provide driver callbacks, sizes and framebuffer
 *
 *  @param ptr the character to print
 *  @return true if success, false otherwise
 */
bool flipdot_gfx_init(flipdot_hw_info_t* ptr)
{
    if (ptr->write_dot_cb == NULL && ptr->write_column_cb == NULL && ptr->write_row_cb == NULL)
    {
        return false; // no callback for interacting with flipdot at all given
    }
    else if (ptr->write_column_cb && ptr->write_row_cb)
    {
        return false; // only support one "mass write" mode
    }
    else if (ptr->columns == 0 || ptr->rows == 0)
    {
        return false; // have to give at least some cols/rows
    }

    hw_info = *ptr; // copy values into RAM

    // determine number of bytes used
    num_col_bytes = (hw_info.columns + 0x7) / 8;
    num_framebuf_bytes = num_col_bytes * hw_info.rows;

    // split given buffer for use as scratchpad and to hold current state
    scratchpad = hw_info.frame_buf;
    curr_state = scratchpad + num_framebuf_bytes;

    return true;
}

/** @brief Draw a single point to the framebuffer
 *
 *  @param x absolute x position
 *  @param y absolute y position
 */
void flipdot_gfx_draw_point(int x, int y)
{
    int bytepos_x = x / 8, bitpos_x = x & 0x7;
    char* buff = scratchpad + (y * num_col_bytes + bytepos_x);

    if (print_inverted)
    {
       *buff &=  ~(1 << bitpos_x);
    }
    else
    {
        *buff |=  (1 << bitpos_x);
    }
};

/** @brief Set behaviour how text and bitmaps shall be printed
 *
 *  @param new_mode if false, a write is done as a set. if true, writing will mean a reset of a dot
 */
void flipdot_gfx_set_printmode(bool new_mode)
{
    print_inverted = new_mode;
}

/** @brief do a set or clear of the entire screen
 *
 *  @param state true to set all dots, false to reset them
 *  @param force true if all dots shall be written regardless of old state, false if only
 *               required dots shall be flipped
 *  @return true if success, false otherwise
 */
bool flipdot_gfx_fill(bool state, bool force)
{
    // write scratchpad in any case
    memset(scratchpad, state ? 0xFF : 0x00, num_framebuf_bytes);

    if (force) // write old buffer with opposite value, so we definitely get a rewrite
    {
        memset(curr_state, state ? 0x00 : 0xFF, num_framebuf_bytes);
    }

    return flipdot_gfx_write_framebuf();
}

/** @brief Show the framebuffer via provided print callback to a console etc.
 *  @details Can be used for debugging, if you don't actually have a display
 */
void flipdot_gfx_dbg_print_framebuf(void)
{
    if (hw_info.print == NULL) // check if print function provided
    {
        return;
    }

    char linebuffer[hw_info.columns + 1]; // + 1 for newline
    
    memset(linebuffer, '-', hw_info.columns);
    linebuffer[hw_info.columns] = '\n';
    
    // print top edge
    hw_info.print(linebuffer, hw_info.columns + 1);

    // show all rows
    for (int row = 0; row < hw_info.rows; row++)
    {
        // show column wise
        for (int col = 0; col < hw_info.columns; col++)
        {
            char tmp_bit = flipdot_gfx_get_bit(row, col, scratchpad);
            char curr_bit = flipdot_gfx_get_bit(row, col, curr_state);

            /* Check state */
            linebuffer[col] = flipdot_gfx_cmp_bits(curr_bit, tmp_bit);        
        }
        linebuffer[hw_info.columns] = '\n';
        hw_info.print(linebuffer, hw_info.columns + 1);
    }
    
    // print bottom edge
    memset(linebuffer, '-', hw_info.columns);
    linebuffer[hw_info.columns] = '\n';
    hw_info.print(linebuffer, hw_info.columns + 1);
}

/** @brief set top right upper corner of whatever shall be printed next
 *
 *  @param row absolute y coordinate (0 based)
 *  @param col absolute x coordinate (0 based)
 */
void flipdot_gfx_set_cursor(int row, int col)
{
    curr_cursor_y = row;
    curr_cursor_x = col;
}

/** @brief relative set top right upper corner of whatever shall be printed next
 *
 *  @param row relative y travel
 *  @param col relative x travel
 */
void flipdot_gfx_set_cursor_relative(int row, int col)
{
    curr_cursor_y += row;
    curr_cursor_x += col;
}


/** @brief draw a circle with the midpoint circle drawing algorithm
 *  @details all coordinates 0 based
 *
 *  @param x0 start x
 *  @param y0 start y
 *  @param r radius
 */
void flipdot_gfx_draw_circle(int x0, int y0, int r)
{
    int x = r, y = 0, E = -r;
    int x_p, y_p;

    int mirror[4][2] = 
    {
        {1, 1},
        {-1, 1},
        {1, -1},
        {-1, -1}
    };

    while(y <= x)
    {
        /* Draw all 8 octants by mirroring along x and y axis */
        for (int op = 0; op < 4; op++)
        {
            x_p = x0 + mirror[op][0] * x;
            y_p = y0 + mirror[op][1] * y;

            if (x_p < 0 || y_p < 0)
            {
                continue; // negative values can be ruled out immediately
            }

            if (x_p < hw_info.columns && y_p < hw_info.rows)
            {
                flipdot_gfx_draw_point(x_p, y_p);
            }
            
            x_p = x0 + mirror[op][0] * y;
            y_p = y0 + mirror[op][1] * x;

            if (x_p < hw_info.columns && y_p < hw_info.rows)
            {
                flipdot_gfx_draw_point(x_p, y_p);
            }
        }

        E += (2 * y + 1);
        y++;

        if (E >= 0)
        {
            E -= (2 * x - 1);
            x--;
        }
    };
}


/** @brief draw a line with the bresenham line drawing algorithm
 *  @details stolen :-) from: http://fredericgoset.ovh/mathematiques/courbes/en/bresenham_line.html
 *           all coordinates 0 based
 *
 *  @param x0 start x
 *  @param y0 start y
 *  @param x1 end x
 *  @param y1 end y
 */
void flipdot_gfx_draw_line(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    int incX = SGN(dx), incY = SGN(dy);
    dx = abs(dx);
    dy = abs(dy);

    if (dy == 0) // horizontal line
    {
        for (int x = x0; x != x1 + incX; x += incX)
        {
            flipdot_gfx_draw_point(x, y0);
        }
    }
    else if (dx == 0) // vertical line
    {
        for (int y = y0; y != y1 + incY; y += incY)
        {
            flipdot_gfx_draw_point(x0, y);
        }
    }
    else if (dx >= dy) // more horizontal than vertical
    {
        int slope = 2 * dy, error = -dx, errorInc = -2 * dx, y = y0;

        for (int x = x0; x != x1 + incX; x += incX)
        {
            flipdot_gfx_draw_point(x, y);
            error += slope;

            if (error >= 0)
            {
                y += incY;
                error += errorInc;
            }
        }
    }
    else // more vertical than horizontal
    {
        int slope = 2 * dx, error = -dy, errorInc = -2 * dy, x = x0;

        for (int y = y0; y != y1 + incY; y += incY)
        {
            flipdot_gfx_draw_point(x, y);
            error += slope;

            if (error >= 0)
            {
                x += incX;
                error += errorInc;
            }
        }
    }
}

/** @brief write a rectangular bitmap into the buffer
 *
 *  @param bitmap pointer to bitmap which shall be written
 *  @param len_x length of bitmap in x direction
 *  @param len_y length of bitmap in y direction
 *  @param move_cursor true if cursor is automatically advanced by len_x
 * 
 *  @return true if at least something could be copied, false otherwise
 */
bool flipdot_gfx_write_bitmap(const char* bitmap, int len_x, int len_y, bool move_cursor)
{
    /* Check if start coordinates make sense */
    if (curr_cursor_y >= hw_info.rows || curr_cursor_x >= hw_info.columns)
    {
        return false;
    }
    /* Check if even some parts are on the buffer */
    else if (curr_cursor_y + len_y < 0 || curr_cursor_x + len_x < 0)
    {
        return false;
    }

    /* check if the start is within buffer, if not we can skip over negative parts */
    int start_x = curr_cursor_x < 0 ? 0 : curr_cursor_x;
    int start_y = curr_cursor_y < 0 ? 0 : curr_cursor_y;

    /* check where we have to end copying over */
    int end_x = curr_cursor_x + len_x >= hw_info.columns ? hw_info.columns : curr_cursor_x + len_x;
    int end_y = curr_cursor_y + len_y >= hw_info.rows ? hw_info.rows : curr_cursor_y + len_y;

    /* Iterate over the framebuffer left to right and top to down. I could be possible that bitmap only
     * partially lies on the buffer. */   
    for (int current_y = start_y; current_y < end_y; current_y++)
    {
        for (int current_x = start_x; current_x < end_x; current_x++)
        {
            // get byte and bit position in buffer
            int x_bytepos = current_x / 8, x_bitpos = current_x & 0x7;

            // get current char of frame buffer
            char* frame_ptr = scratchpad + (current_y * num_col_bytes + x_bytepos);

            // index new char which shall be written to buffer, but within coordinates of bitmap
            char bmp_char = bitmap[(current_y-curr_cursor_y) * len_x + (current_x-curr_cursor_x)];

            if (print_inverted) // switch around logic in case inverted mode is active
            {
                bmp_char = bmp_char == FLIPDOT_SET ? FLIPDOT_RESET : FLIPDOT_SET;
            }

            if (bmp_char == FLIPDOT_SET)
            {
                *frame_ptr |= (1 << x_bitpos);
            }
            else
            {
                *frame_ptr &= ~(1 << x_bitpos);
            }
        }
    }

    if (move_cursor)
    {
        flipdot_gfx_set_cursor_relative(0, end_x - start_x);
    }

    return true;
}

/** @brief write a 5x7 char to the buffer
 *
 *  @param format NULL terminated string to write
 */
void flipdot_gfx_write_5x7_line(char* format)
{
    int idx = 0;
    while(format[idx] != '\0') // iterate as long as chars are there
    {
        const char* glyph = get_5x7_bitmap(format[idx]); // obtain bitmap
        flipdot_gfx_write_bitmap(glyph, 5, 7, true); // write it

        // in case letters are not aligned by "monospace" grid, write a vertical blank line
        glyph = get_1x7_blanking();
        flipdot_gfx_write_bitmap(glyph, 1, 7, true); // will also advance cursor by a space

        idx++; // jump to next char
    }
}

/** @brief sets new framebuffer contents
 *
 *  @return true if success, false otherwise
 */
bool flipdot_gfx_write_framebuf(void)
{
    bool ret = true; // to remember overall success

    if (hw_info.write_column_cb)
    {
        char data[hw_info.rows];

        for (int col = 0; col < hw_info.columns; col++)
        {
            bool rewriteNeeded = false;

            /* collect column data, since it's not continuous in memory */
            for (int row = 0; row < hw_info.rows; row++)
            {
                bool newBit = flipdot_gfx_get_bit(row, col, scratchpad);
                bool oldBit = flipdot_gfx_get_bit(row, col, curr_state);

                data[row] = flipdot_gfx_cmp_bits(oldBit, newBit);
                
                if (newBit != oldBit)
                {
                    rewriteNeeded = true;
                }
            }

            // determine if a rewrite is even needed
            if (rewriteNeeded == false)
            {
                continue;
            }

            ret &= hw_info.write_column_cb(col, data);
        }
    }
    else
    {
        char data[hw_info.columns];

        for (int row = 0; row < hw_info.rows; row++)
        {
            bool rewriteNeeded = false;

            for (int col = 0; col < hw_info.columns; col++)
            {
                bool newBit = flipdot_gfx_get_bit(row, col, scratchpad);
                bool oldBit = flipdot_gfx_get_bit(row, col, curr_state);

                data[col] = flipdot_gfx_cmp_bits(oldBit, newBit);

                // determine if a rewrite is even needed
                if (newBit == oldBit)
                {
                    continue;
                }

                // check with scheme shall be used to update flipdot with frame buffer
                if (hw_info.write_dot_cb)
                {
                    ret &= hw_info.write_dot_cb(row, col, data[0]);
                }

                rewriteNeeded = true;
            }

            if (hw_info.write_row_cb && rewriteNeeded)
            {
                ret &= hw_info.write_row_cb(row, data);
            }
        }
    }

    // output result for debugging
    // flipdot_gfx_dbg_print_framebuf();

    // set buffer to "steady state", so that driver callbacks could utilize meta states previously
    memcpy(curr_state, scratchpad, num_framebuf_bytes);

    // output result for debugging
    flipdot_gfx_dbg_print_framebuf();

    return ret;
}


/** @brief write a 5x7 char to the buffer
 *
 *  @param format NULL terminated string to write
 *  @param shift_step number of dots to shift text per call of this function
 *  @param first_shift true when this function was initially called
 * 
 *  @return true if string is once completely shifted, false otherwise
 */
bool flipdot_gfx_shift_5x7_line(char* format, int shift_step, bool first_shift)
{
    static int start_cursor, first_start;
    int len = strlen(format) * (5 + 1); // check how long string is and how many dots it takes
    bool start_over = (shift_step > 0 && start_cursor >= hw_info.columns); // stop when start of dots is in right side
    start_over |= (shift_step < 0 && curr_cursor_x < 0); // stop when end of dots is on left side
    
    if (first_shift) // check if initial frame is set up
    {
        start_cursor = curr_cursor_x;
        first_start = curr_cursor_x;
    }
    else if (!start_over) // there is some data left on the display, shift it
    {
        start_cursor += shift_step;
    }
    /* can start to bring in new characters again */
    else if (shift_step > 0) // shift to the right, have to start over from left 
    {
        start_cursor = -len; // let cursor start from the very left
    }
    else // shift to the left, start over from right
    {
        start_cursor = hw_info.columns - 1;
    }

    int idx = 0;
    if (start_cursor < -5) // skip "useless" characters which are too far to the left
    {
        idx = abs(start_cursor) / 6; // first char to print
        flipdot_gfx_set_cursor(curr_cursor_y, start_cursor + idx * 6); // move cursor respectively
    }
    else
    {
        // update our current cursor
        flipdot_gfx_set_cursor(curr_cursor_y, start_cursor);
    }

    // clear out from previous writes, do it only for affected rows
    char* start = scratchpad + (curr_cursor_y * num_col_bytes);
    memset(start, print_inverted ? 0xFF : 0x00, num_col_bytes * 7);

    while(format[idx] != '\0') // iterate as long as chars are there
    {
        if (curr_cursor_x >= hw_info.columns) // print from left to right, stop if we are beyond buffer
        {
            break;
        }
        else // possible to print at least one dot into frame
        {
            int old_x = curr_cursor_x; // remember old cursor pos
            int remaining_shift;

            char tmp_buff[2] = {format[idx], '\0'}; // to re-use the line write function
            flipdot_gfx_write_5x7_line(tmp_buff);

            // check by how much we have to force the cursor to the right
            remaining_shift = 6 - (curr_cursor_x - old_x);
            flipdot_gfx_set_cursor_relative(0, remaining_shift);
        }

        idx++; // jump to next char
    }

    return ((first_shift == false) && (start_cursor == first_start));
}


//************************************************************************
// Private functions
//************************************************************************

/** @brief compare old and new framebuffer bits
 *
 *  @param old previous bit state
 *  @param new desired upcoming bit state
 *  @return a value of flipdot_states_t which reflects next action
 */
static inline flipdot_states_t flipdot_gfx_cmp_bits(bool old, bool new)
{
    if (old == new)
    {
        return old ? FLIPDOT_SET : FLIPDOT_RESET;
    }
    else if (old && !new)
    {
        return FLIPDOT_NEW_RESET;
    }
    else
    {
        return FLIPDOT_NEW_SET;
    }
}

/** @brief get the state of a flipdot from a frame buffer
 *
 *  @param row y coordinate
 *  @param col x coordinate
 *  @param framebuf pointer to respective buffer
 *  @return false if bit is not set, true otherwise
 */
static inline bool flipdot_gfx_get_bit(int row, int col, char* framebuf)
{
    /* mask out current bit */
    return framebuf[row * num_col_bytes + (col / 8)] & ( 1 << (col & 0x7));
}
