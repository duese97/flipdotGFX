#include <stddef.h>
#include <string.h> // for memset,..

#include <flipdotGFX.h>
#include <characterROM.h>

/* Local macros */
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))


//************************************************************************
// Local variables
//************************************************************************
static flipdot_hw_info_t hw_info;   // local copy of given HW info struct

// current printing position
static int curr_cursor_x;
static int curr_cursor_y;

// if true, drawing will be be inverted
static bool print_inverted = false;

//************************************************************************
// Local functions/helpers declarations
//************************************************************************
static bool flipdot_gfx_check_rewrite(char* buff);


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

    return true;
}

/** @brief Draw a single point to the framebuffer
 *
 *  @param x absolute x position
 *  @param y absolute y position
 */
void flipdot_gfx_draw_point(int x, int y)
{
    char* buff = &hw_info.frame_buf[y * hw_info.columns + x];
    flipdot_states_t new_state = print_inverted ? FLIPDOT_NEW_RESET : FLIPDOT_NEW_SET;

    // check if a write is needed
    if ((*buff == FLIPDOT_SET && new_state == FLIPDOT_NEW_RESET) ||
        (*buff == FLIPDOT_RESET && new_state == FLIPDOT_NEW_SET) ||
        (*buff != new_state)) // overwrite old state
    {
        *buff = new_state;
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
    if (force) // set new elements anyway
    {
        memset(hw_info.frame_buf, state ? FLIPDOT_NEW_SET : FLIPDOT_NEW_RESET, hw_info.columns * hw_info.rows);
    }
    else
    {
        // iterate over entire framebuffer
        for (int idx = 0; idx < hw_info.columns * hw_info.rows; idx++)
        {
            // check if element really has to be set
            if (state && hw_info.frame_buf[idx] != FLIPDOT_SET)
            {
                 hw_info.frame_buf[idx] = FLIPDOT_NEW_SET;
            }
            else if (!state && hw_info.frame_buf[idx] != FLIPDOT_RESET)
            {
                hw_info.frame_buf[idx] = FLIPDOT_NEW_RESET;
            }
        }
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

    char separator[hw_info.columns];
    char newline = '\n';
    memset(separator, '-', hw_info.columns);
    
    // print top edge
    hw_info.print(separator, hw_info.columns);
    hw_info.print(&newline, 1);

    // show all rows
    for (int row = 0; row < hw_info.rows; row++)
    {
        // copy over data
        hw_info.print(&hw_info.frame_buf[row * hw_info.columns], hw_info.columns);
        hw_info.print(&newline, 1);
    }
    
    // print bottom edge
    hw_info.print(separator, hw_info.columns);
    hw_info.print(&newline, 1);
}

/** @brief set top right upper corner of whatever shall be printed next
 *
 *  @param row absolute y coordinate (0 based)
 *  @param col absolute x coordinate (0 based)
 */
void flipdot_gfx_set_cursor(int row, int col)
{
    if (row < hw_info.rows && col < hw_info.columns)
    {
        curr_cursor_y = row;
        curr_cursor_x = col;
    }
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

    /* Make sure cursor is within bounds of frame */
    if (curr_cursor_y >= hw_info.rows)
    {
        curr_cursor_y = hw_info.rows - 1;
    }
    else if (curr_cursor_y < 0)
    {
        curr_cursor_y = 0;
    }

    if (curr_cursor_x >=hw_info.columns )
    {
        curr_cursor_x = hw_info.columns  - 1;
    }
    else if (curr_cursor_x < 0)
    {
        curr_cursor_x = 0;
    }
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
 */
void flipdot_gfx_write_bitmap(const char* bitmap, int len_x, int len_y, bool move_cursor)
{
    /* Iterate over the framebuffer left to right and top to down */   
    for (int current_y = curr_cursor_y; (current_y < curr_cursor_y + len_y) && (current_y < hw_info.rows); current_y++)
    {
        for (int current_x = curr_cursor_x; (current_x < curr_cursor_x + len_x) && (current_x < hw_info.columns); current_x++)
        {
            // get current char of frame buffer
            char* frame_ptr = &hw_info.frame_buf[current_y * hw_info.columns + current_x];
            // index new char which shall be written to buffer, but within coordinates of bitmap
            char bmp_char = bitmap[(current_y-curr_cursor_y) * len_x + (current_x-curr_cursor_x)];

            if (print_inverted) // switch around logic in case inverted mode is active
            {
                bmp_char = bmp_char == FLIPDOT_SET ? FLIPDOT_RESET : FLIPDOT_SET;
            }

            if (*frame_ptr == FLIPDOT_NEW_SET || *frame_ptr == FLIPDOT_NEW_RESET) // skip if the cell already has to be set
            {
                continue;
            }
            else if (*frame_ptr == bmp_char) // skip if the dot already has the proper state
            {
                continue;
            }
            else if (*frame_ptr == FLIPDOT_SET && bmp_char == FLIPDOT_RESET) // change state from set -> reset
            {
                *frame_ptr = FLIPDOT_NEW_RESET;
            }
            else if (*frame_ptr == FLIPDOT_RESET && bmp_char == FLIPDOT_SET) // change state from reset -> set
            {
                *frame_ptr = FLIPDOT_NEW_SET;
            }
        }
    }

    if (move_cursor)
    {
        flipdot_gfx_set_cursor_relative(0, len_x);
    }
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
        char data[hw_info.columns];

        for (int col = 0; col < hw_info.columns; col++)
        {
            /* collect column data, since it's not continuous in memory */
            for (int row = 0; row < hw_info.rows; row++)
            {
                data[row] = hw_info.frame_buf[row * hw_info.columns + col];
            }

            // determine if a rewrite is even needed
            if (flipdot_gfx_check_rewrite(data) == false)
            {
                continue;
            }

            ret &= hw_info.write_column_cb(col, data);
        }
    }
    else
    {
        for (int row = 0; row < hw_info.rows; row++)
        {
            for (int col = 0; col < hw_info.columns; col++)
            {
                // helper to shorten access to array
                char* startPtr = &hw_info.frame_buf[row * hw_info.columns + col];

                // determine if a rewrite is even needed
                if (flipdot_gfx_check_rewrite(startPtr) == false)
                {
                    continue;
                }

                // check with scheme shall be used to update flipdot with frame buffer
                if (hw_info.write_dot_cb)
                {
                    ret &= hw_info.write_dot_cb(row, col, *startPtr);
                }
                else if (hw_info.write_row_cb)
                {
                    ret &= hw_info.write_row_cb(row, startPtr);
                    break;
                }
            }
        }
    }

    // output result for debugging
    // flipdot_gfx_dbg_print_framebuf();

    // set buffer to "steady state", so that driver callbacks could utilize meta states previously
    for (int idx = 0; idx < hw_info.columns * hw_info.rows; idx++)
    {
        if (hw_info.frame_buf[idx] == FLIPDOT_NEW_SET)
        {
            hw_info.frame_buf[idx] = FLIPDOT_SET;
        }
        else if (hw_info.frame_buf[idx] == FLIPDOT_NEW_RESET)
        {
            hw_info.frame_buf[idx] = FLIPDOT_RESET;
        }
    }

    // output result for debugging
    flipdot_gfx_dbg_print_framebuf();

    return ret;
}


//************************************************************************
// Private functions
//************************************************************************

/** @brief checks if a rewrite is required, depending on write scheme
 *
 *  @param buff pointer to single dot/row or column buffer
 *  @return true if rewrite is needed, false otherwise
 */
static bool flipdot_gfx_check_rewrite(char* buff)
{
    int size; // to remember how many elements need to be checked

    // find out size
    if (hw_info.write_dot_cb)
    {
        size = 1;
    }
    else if (hw_info.write_column_cb)
    {
        size = hw_info.columns;
    }
    else
    {
        size = hw_info.rows;
    }

    for (int idx = 0; idx < size; idx++) // step over buffer
    {
        // check if anything new has to be set or reset
        if (buff[idx] == FLIPDOT_NEW_SET || buff[idx] == FLIPDOT_NEW_RESET)
        {
            return true;
        }
    }

    return false; // nothing found
}