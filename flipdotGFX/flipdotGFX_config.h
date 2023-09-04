#ifndef _FLIPDOT_GFX_CONFIG_H_
#define _FLIPDOT_GFX_CONFIG_H_

/* Various compile switches to save some memory, if needed. comment out in this case */
#define USE_UPPERCASE_5x7
#define USE_LOWERCASE_5x7
#define USE_NUMBERS_5x7
#define USE_SYMBOLS1_5x7 // ascii ! to /
#define USE_SYMBOLS2_5x7 // ascii : to @
#define USE_SYMBOLS3_5x7 // ascii [ to `
#define USE_SYMBOLS4_5x7 // ascii { to ~

#define PREFER_SPEED // if set, will use faster framebuffer calculations at cost of memory

#endif // _FLIPDOT_GFX_CONFIG_H_
