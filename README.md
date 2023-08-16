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
- ```flipdot_gfx_init```
- ```flipdot_gfx_dbg_print_framebuf``` : Output current print buffer to console. Example usage where a 28 x 19 flipdot is simulated:
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

# Example Usage