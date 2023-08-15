#include "characterROM.h"
#include "flipdotGFX_config.h"

static const char bitmap_5x7_space[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};


#ifdef USE_NUMBERS_5x7
static const char bitmap_5x7_0[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', 'X', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_1[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_2[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_3[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_4[7][5]=
{
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', ' ', ' ', 'X', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '}
};

static const char bitmap_5x7_5[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_6[7][5]=
{
    {' ', ' ', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_7[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '}
};

static const char bitmap_5x7_8[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_9[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', 'X', 'X', ' ', ' '}
};

#endif // USE_NUMBERS_5x7

static const char bitmap_5x7_colon[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_questionmark[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_A[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_B[7][5]=
{
    {'X', 'X', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_C[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_D[7][5]=
{
    {'X', 'X', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_E[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_F[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_G[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_H[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_I[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_J[7][5]=
{
    {' ', ' ', 'X', 'X', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {'X', ' ', ' ', 'X', ' '},
    {' ', 'X', 'X', ' ', ' '}
};

static const char bitmap_5x7_K[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', 'X', ' '},
    {'X', ' ', 'X', ' ', ' '},
    {'X', 'X', ' ', ' ', ' '},
    {'X', ' ', 'X', ' ', ' '},
    {'X', ' ', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_L[7][5]=
{
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_M[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', ' ', 'X', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_N[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_O[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_P[7][5]=
{
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_Q[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', ' '},
    {' ', 'X', 'X', ' ', 'X'}
};

static const char bitmap_5x7_R[7][5]=
{
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', 'X', ' ', ' '},
    {'X', ' ', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_S[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_T[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_U[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_V[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_W[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '}
};

static const char bitmap_5x7_X[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_Y[7][5]=
{
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_Z[7][5]=
{
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};

/* SKIPPING LOWERCASE FOR NOW */


// a placeholder for non supported bitmaps
static const char bitmap_5x7_void;

/*
static const char bitmap_5x7_[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};
*/

const char* bitmap_lookup [] =
{
    &bitmap_5x7_space[0][0],

    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,

    /* 0 - 9 */
#ifdef USE_NUMBERS_5x7
    &bitmap_5x7_0[0][0],
    &bitmap_5x7_1[0][0],
    &bitmap_5x7_2[0][0],
    &bitmap_5x7_3[0][0],
    &bitmap_5x7_4[0][0],
    &bitmap_5x7_5[0][0],
    &bitmap_5x7_6[0][0],
    &bitmap_5x7_7[0][0],
    &bitmap_5x7_8[0][0],
    &bitmap_5x7_9[0][0],
#else
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
#endif // USE_NUMBERS_5x7

    /* */
    &bitmap_5x7_colon[0][0],
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_questionmark[0][0],
    &bitmap_5x7_void,

    /* A - Z */
#ifdef USE_UPPERCASE_5x7
    &bitmap_5x7_A[0][0],
    &bitmap_5x7_B[0][0],
    &bitmap_5x7_C[0][0],
    &bitmap_5x7_D[0][0],
    &bitmap_5x7_E[0][0],
    &bitmap_5x7_F[0][0],
    &bitmap_5x7_G[0][0],
    &bitmap_5x7_H[0][0],
    &bitmap_5x7_I[0][0],
    &bitmap_5x7_J[0][0],
    &bitmap_5x7_K[0][0],
    &bitmap_5x7_L[0][0],
    &bitmap_5x7_M[0][0],
    &bitmap_5x7_N[0][0],
    &bitmap_5x7_O[0][0],
    &bitmap_5x7_P[0][0],
    &bitmap_5x7_Q[0][0],
    &bitmap_5x7_R[0][0],
    &bitmap_5x7_S[0][0],
    &bitmap_5x7_T[0][0],
    &bitmap_5x7_U[0][0],
    &bitmap_5x7_V[0][0],
    &bitmap_5x7_W[0][0],
    &bitmap_5x7_X[0][0],
    &bitmap_5x7_Y[0][0],
    &bitmap_5x7_Z[0][0],
#else
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
#endif // USE_UPPERCASE_5x7

    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,

    /* a - z */
#ifdef USE_LOWERCASE_5x7
#else
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
    &bitmap_5x7_void,
#endif // USE_LOWERCASE_5x7
};

// returns appropriate bitmap for a given (printable) ascii
const char* get_5x7_bitmap(char c)
{
    char target = c;

    if (target >='a' && target <= 'z') // if lowercase is used nonetheless: make to uppercase
    {
#if !defined(USE_LOWERCASE_5x7) && defined(USE_UPPERCASE_5x7)
        target -= 0x20;
#endif // !defined(USE_LOWERCASE_5x7) && defined(USE_UPPERCASE_5x7)
    }
    else if (target >= 'A' && target <= 'Z') // if uppercase is used nonetheless: make to lowercase
    {
#if !defined(USE_UPPERCASE_5x7) && defined(USE_LOWERCASE_5x7)
        target += 0x20;
#endif // !defined(USE_UPPERCASE_5x7) && defined(USE_LOWERCASE_5x7)
    }

    if (target < ' ' || target > '~') // start off with normal printable characters
    {
        target = '?';
    }
    else if (bitmap_lookup[target - ' '] == &bitmap_5x7_void) // check if symbol is supported
    {
        target = '?';
    }

    target -= ' '; // use char as index so we can start indexing in table
    return bitmap_lookup[target];
}
