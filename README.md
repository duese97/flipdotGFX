# flipdotGFX
A small and simple "graphics" library for flipdot displays. You can draw your own bitmaps, a pre-defined 5x7 monospace font and basic shapes like lines and circles.

# Features
- Designed for quick refresh rates of display. Dot-, row- or column wise writing is supported. Respective driver will only be called, when dots actually have to be flipped.
- Flash footprint can be lowered by picking uppercase, lowercase, numbers or special ASCII characters.
- Framebuffer can be printed as a debug option. So even if (currently) no flipdot hardware is available, you can visualize the outcome.
- TBD

# Issues
- Much memory is wasted for the bitmaps/font (flash) and framebuffer (RAM). Could be optimized.
- CPU runtime is often not ideal


# Functions
Small overview over all public functions:
- ```flipdot_gfx_init```: Setup available columns, rows, driving scheme etc.
- ```flipdot_gfx_set_printmode```: Decide if a print shall equal a set or a reset of a respective dot
- ```flipdot_gfx_fill```: Fill the entire display with a set or reset pattern
- ```flipdot_gfx_write_framebuf```: Must be called when all frame contents are setup. Will then utilize provided callbacks to build the frame.
- ```flipdot_gfx_set_cursor``` and ```flipdot_gfx_set_cursor_relative```: Useful for text/bitmap printing, set top right starting corner
- ```flipdot_gfx_write_5x7_line```: Write a ASCII string with the 5x7 monospace font
- ```flipdot_gfx_shift_5x7_line```: Same as ```flipdot_gfx_write_5x7_line```, but can shift a arbitrarily long text from left to right or vice versa. Each function call will move the text by the desired amount.
- ```flipdot_gfx_write_bitmap```: Write an arbitrary (user created) bitmap. It must be setup like this:
```
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
```
- ```flipdot_gfx_draw_point```,```flipdot_gfx_draw_circle``` and ```flipdot_gfx_draw_line```: Basic geometric shapes
- ```flipdot_gfx_dbg_print_framebuf```: Output current print buffer to console. Example usage where a 28 x 19 flipdot is simulated:
```
----------------------------

  X    XXX      XXX   XXX   
 XX   X   X XX X   X X   X
  X       X XX     X X   X
  X     XX       XX   XXXX
  X    X    XX     X     X
  X   X     XX X   X    X
 XXX  XXXXX     XXX   XX    











----------------------------
```
# Driver usage
You have to provide your own driver functions and hand them over to the library. This is one in the init struct, with the members
```
    bool (*write_dot_cb)(int row, int col, char state);
    bool (*write_column_cb)(int col, char* states);
    bool (*write_row_cb)(int row, char* states);
```
The Parameter state/states points to the data to be written.
There are four values for this state:
- 'R' means the respective dot has to be freshly reset 
- 'S' means the dot has to be freshly set
- ' ' means dot is already reset, can be skipped
- 'X' means the dot is set, no need to drive it again

For a row-wise driving this looks something like this:
```
      X          R S  X
```
In C-style syntax the "states" pointer would point to this equivalent structure:
```
states = {' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'R', ' ', 'S', ' ', ' ', 'X'};
```

# Example Usage
An example implementation for an ESP32 with the arduino framework is provided in main.cpp. Some text is displayed as well as a very basic clock, where only the seconds hand is shown.