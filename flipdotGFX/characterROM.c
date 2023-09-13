#include "characterROM.h"
#include <stddef.h> // for NULL
#include <string.h> // for memset,..

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


//************************************************************************
// USE_SYMBOLS1_5x7
//************************************************************************
static const char bitmap_5x7_excl_mark[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_double_quote[7][5]=
{
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_hash[7][5]=
{
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '}
};

static const char bitmap_5x7_dollar[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', 'X'},
    {'X', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {' ', ' ', 'X', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_percent[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', 'X'},
    {'X', ' ', ' ', 'X', 'X'}
};

static const char bitmap_5x7_and[7][5]=
{
    {' ', 'X', 'X', ' ', ' '},
    {'X', ' ', ' ', 'X', ' '},
    {'X', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', ' '},
    {' ', 'X', 'X', ' ', 'X'}
};

static const char bitmap_5x7_single_quote[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_open_bracket[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_closing_bracket[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_asterisk[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {'X', ' ', 'X', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', 'X', ' ', 'X'},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_plus[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_comma[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_minus[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_dot[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', ' ', ' '},
    {' ', 'X', 'X', ' ', ' '}
};

static const char bitmap_5x7_slash[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '}
};


//************************************************************************
// USE_NUMBERS_5x7
//************************************************************************
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


//************************************************************************
// USE_SYMBOLS2_5x7
//************************************************************************
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

static const char bitmap_5x7_semicolon[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_less_than[7][5]=
{
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_equal[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_greater_than[7][5]=
{
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '}
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

static const char bitmap_5x7_at[7][5]=
{
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};


//************************************************************************
// USE_UPPERCASE_5x7
//************************************************************************
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


//************************************************************************
// USE_SYMBOLS3_5x7
//************************************************************************
static const char bitmap_5x7_square_bracket_open[7][5]=
{
    {'X', 'X', 'X', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', ' ', ' '}
};

static const char bitmap_5x7_backslash[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_square_bracket_closing[7][5]=
{
    {' ', ' ', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', 'X', 'X', 'X'}
};

static const char bitmap_5x7_superscript[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_underscore[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};


//************************************************************************
// USE_LOWERCASE_5x7
//************************************************************************
static const char bitmap_5x7_a[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_b[7][5]=
{
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', 'X', ' '},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_c[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_d[7][5]=
{
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'}
};

static const char bitmap_5x7_e[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_f[7][5]=
{
    {' ', ' ', 'X', 'X', ' '},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', ' ', ' '},
    {'X', 'X', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '}
};

static const char bitmap_5x7_g[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_h[7][5]=
{
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', 'X', ' '},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_i[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_j[7][5]=
{
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_k[7][5]=
{
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {' ', 'X', ' ', ' ', 'X'}
};

static const char bitmap_5x7_l[7][5]=
{
    {' ', 'X', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_m[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', ' ', 'X', ' '},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'}
};

static const char bitmap_5x7_n[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', 'X', ' '},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_o[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_p[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_q[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', 'X'},
    {' ', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_r[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', 'X', 'X', ' '},
    {'X', 'X', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '}
};

static const char bitmap_5x7_s[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {'X', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_t[7][5]=
{
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', 'X', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', 'X', ' '}
};

static const char bitmap_5x7_u[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', 'X', 'X'},
    {' ', 'X', 'X', ' ', 'X'}
};

static const char bitmap_5x7_v[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_w[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {'X', ' ', 'X', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '}
};

static const char bitmap_5x7_x[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', 'X', ' '},
    {'X', ' ', ' ', ' ', 'X'}
};

static const char bitmap_5x7_y[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', 'X'},
    {'X', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', 'X', 'X', 'X', ' '}
};

static const char bitmap_5x7_z[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', 'X', 'X', 'X', 'X'}
};


//************************************************************************
// USE_SYMBOLS4_5x7
//************************************************************************
static const char bitmap_5x7_open_brace[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {'X', ' ', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', 'X', ' ', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_pipe[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_closing_brace[7][5]=
{
    {' ', ' ', 'X', ' ', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', 'X'},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', 'X', ' '},
    {' ', ' ', 'X', ' ', ' '}
};

static const char bitmap_5x7_tilde[7][5]=
{
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', 'X', 'X', ' ', 'X'},
    {'X', ' ', ' ', 'X', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};


const char* bitmaps_5x7_symbols1[]=
{
    &bitmap_5x7_excl_mark[0][0],
    &bitmap_5x7_double_quote[0][0],
    &bitmap_5x7_hash[0][0],
    &bitmap_5x7_dollar[0][0],
    &bitmap_5x7_percent[0][0],
    &bitmap_5x7_and[0][0],
    &bitmap_5x7_single_quote[0][0],
    &bitmap_5x7_open_bracket[0][0],
    &bitmap_5x7_closing_bracket[0][0],
    &bitmap_5x7_asterisk[0][0],
    &bitmap_5x7_plus[0][0],
    &bitmap_5x7_comma[0][0],
    &bitmap_5x7_minus[0][0],
    &bitmap_5x7_dot[0][0],
    &bitmap_5x7_slash[0][0]
};

const char* bitmaps_5x7_0_9[] =
{
    &bitmap_5x7_0[0][0],
    &bitmap_5x7_1[0][0],
    &bitmap_5x7_2[0][0],
    &bitmap_5x7_3[0][0],
    &bitmap_5x7_4[0][0],
    &bitmap_5x7_5[0][0],
    &bitmap_5x7_6[0][0],
    &bitmap_5x7_7[0][0],
    &bitmap_5x7_8[0][0],
    &bitmap_5x7_9[0][0]
};

const char* bitmaps_5x7_symbols2[] =
{
    &bitmap_5x7_colon[0][0],
    &bitmap_5x7_semicolon[0][0],
    &bitmap_5x7_less_than[0][0],
    &bitmap_5x7_equal[0][0],
    &bitmap_5x7_greater_than[0][0],
    &bitmap_5x7_questionmark[0][0],
    &bitmap_5x7_at[0][0]
};

const char* bitmaps_5x7_A_Z[] =
{
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
    &bitmap_5x7_Z[0][0]
};

const char* bitmaps_5x7_symbols3[] =
{
    &bitmap_5x7_square_bracket_open[0][0],
    &bitmap_5x7_backslash[0][0],
    &bitmap_5x7_square_bracket_closing[0][0],
    &bitmap_5x7_superscript[0][0],
    &bitmap_5x7_underscore[0][0]
};

const char* bitmaps_5x7_a_z[] =
{
    &bitmap_5x7_a[0][0],
    &bitmap_5x7_b[0][0],
    &bitmap_5x7_c[0][0],
    &bitmap_5x7_d[0][0],
    &bitmap_5x7_e[0][0],
    &bitmap_5x7_f[0][0],
    &bitmap_5x7_g[0][0],
    &bitmap_5x7_h[0][0],
    &bitmap_5x7_i[0][0],
    &bitmap_5x7_j[0][0],
    &bitmap_5x7_k[0][0],
    &bitmap_5x7_l[0][0],
    &bitmap_5x7_m[0][0],
    &bitmap_5x7_n[0][0],
    &bitmap_5x7_o[0][0],
    &bitmap_5x7_p[0][0],
    &bitmap_5x7_q[0][0],
    &bitmap_5x7_r[0][0],
    &bitmap_5x7_s[0][0],
    &bitmap_5x7_t[0][0],
    &bitmap_5x7_u[0][0],
    &bitmap_5x7_v[0][0],
    &bitmap_5x7_w[0][0],
    &bitmap_5x7_x[0][0],
    &bitmap_5x7_y[0][0],
    &bitmap_5x7_z[0][0]
};

const char* bitmaps_5x7_symbols4[] =
{
    &bitmap_5x7_open_brace[0][0],
    &bitmap_5x7_pipe[0][0],
    &bitmap_5x7_closing_brace[0][0],
    &bitmap_5x7_tilde[0][0]
};


/* Special "blanking" line which has to be inserted in between chars, if they are not aligned*/
static const char bitmap_1x7_space[7][1] =
{
    { ' ' },
    { ' ' },
    { ' ' },
    { ' ' },
    { ' ' },
    { ' ' },
    { ' ' }
};

#ifdef USE_LAZY_10x14
char bitmap_10x14_buffer[14][10]; // to temporarily hold a upscaled bitmap in RAM

/** @brief convert a given 5x7 bitmap into a 10x14 scaled one
 * 
 *  @param orig_ptr pointer to a 5x7 bitmap
 */
void convert_5x7_to_10x14(const char* orig_ptr)
{
    for (int row = 0; row <= 12; )
    {
        for (int col = 0; col <= 8; )
        {
            bitmap_10x14_buffer[row][col] = (char)orig_ptr[(row/2) * 5 + col/2];
            bitmap_10x14_buffer[row][col + 1] = bitmap_10x14_buffer[row][col]; // duplicate column cell which is to the left

            col += 2;
        }
        // duplicate row once below
        memcpy(bitmap_10x14_buffer[row + 1], bitmap_10x14_buffer[row], sizeof(bitmap_10x14_buffer[0]));
        row += 2; // can iterate over every second row
    }
}
#endif // USE_LAZY_10x14


/** @brief get a blank line bitmap
 *  @details might be used to fill space in between characters
 * 
 *  @param font tye of font to be used
 *  @return pointer to bitmap
 */
const char* get_blanking(flipdot_fonttype_t font)
{
    const char* ret_ptr = &bitmap_1x7_space[0][0];

#ifdef USE_LAZY_10x14
    if (font == MONOSPACE_10x14_LAZY)
    {
        memset(bitmap_10x14_buffer, ' ', 14 * 2);
        ret_ptr = (const char*)bitmap_10x14_buffer;
    }
#endif // USE_LAZY_10x14

    return ret_ptr;
}

/** @brief get appropriate bitmap for a given (printable) ASCII
 *
 *  @param c character where a bitmap is desired
 *  @param font type of font to return
 *  @return pointer to bitmap, "?" if unsupported
 */
const char* get_monospace_bitmap(char c, flipdot_fonttype_t font)
{
    char target = c;
    const char* ret_ptr = NULL;

    if (target >= 'a' && target <= 'z')
    {
#if !defined(USE_LOWERCASE_5x7) && defined(USE_UPPERCASE_5x7)
        target -= 0x20; // if lowercase is used nonetheless: make to uppercase
#endif // !defined(USE_LOWERCASE_5x7) && defined(USE_UPPERCASE_5x7)
    }
    else if (target >= 'A' && target <= 'Z')
    {
#if !defined(USE_UPPERCASE_5x7) && defined(USE_LOWERCASE_5x7)
        target += 0x20; // if uppercase is used nonetheless: make to lowercase
#endif // !defined(USE_UPPERCASE_5x7) && defined(USE_LOWERCASE_5x7)
    }

    /* Check if symbol is supported */
#ifdef USE_NUMBERS_5x7
    if (target >= '0' && target <= '9')
    {
        ret_ptr = bitmaps_5x7_0_9[target - '0'];
    }
#endif // USE_NUMBERS_5x7

#ifdef USE_UPPERCASE_5x7
    if (target >= 'A' && target <= 'Z')
    {
        ret_ptr = bitmaps_5x7_A_Z[target - 'A'];
    }
#endif // USE_UPPERCASE_5x7

#ifdef USE_LOWERCASE_5x7
    if (target >= 'a' && target <= 'z')
    {
        ret_ptr = bitmaps_5x7_a_z[target - 'a'];
    }
#endif // USE_LOWERCASE_5x7

    if (target == ' ')
    {
        ret_ptr = &bitmap_5x7_space[0][0];
    }

#ifdef USE_SYMBOLS1_5x7
    if (target >= '!' && target <= '/')
    {
        ret_ptr = bitmaps_5x7_symbols1[target - '!'];
    }
#endif // USE_SYMBOLS1_5x7

#ifdef USE_SYMBOLS2_5x7
    if (target >= ':' && target <= '@')
    {
        ret_ptr = bitmaps_5x7_symbols2[target - ':'];
    }
#endif // USE_SYMBOLS2_5x7

#ifdef USE_SYMBOLS3_5x7
    if (target >= '[' && target <= '_')
    {
        ret_ptr = bitmaps_5x7_symbols3[target - '['];
    }
#endif // USE_SYMBOLS3_5x7

#ifdef USE_SYMBOLS4_5x7
    if (target >= '{' && target <= '~')
    {
        ret_ptr = bitmaps_5x7_symbols4[target - '{'];
    }
#endif // USE_SYMBOLS4_5x7

    if (ret_ptr == NULL) // unsupported, not yet set
    {
        ret_ptr = &bitmap_5x7_questionmark[0][0];
    }

#ifdef USE_LAZY_10x14
    if (font == MONOSPACE_10x14_LAZY)
    {
        convert_5x7_to_10x14(ret_ptr);

        ret_ptr = (const char*)&bitmap_10x14_buffer[0][0];
    }
#endif // USE_LAZY_10x14

    return ret_ptr;
}
