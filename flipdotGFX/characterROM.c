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

static const char bitmap_5x7_quote[7][5]=
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
const char* bitmaps_5x7_symbols1[]=
{
    &bitmap_5x7_excl_mark[0][0],
    &bitmap_5x7_quote[0][0],
    &bitmap_5x7_hash[0][0],
    &bitmap_5x7_dollar[0][0],
    &bitmap_5x7_percent[0][0],
    &bitmap_5x7_and[0][0],
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

const char* get_1x7_blanking(void)
{
    return &bitmap_1x7_space[0][0];
}

// returns appropriate bitmap for a given (printable) ascii
const char* get_5x7_bitmap(char c)
{
    char target = c;

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
        target -= '0';
        return bitmaps_5x7_0_9[target];
    }
#endif // USE_NUMBERS_5x7

#ifdef USE_UPPERCASE_5x7
    if (target >= 'A' && target <= 'Z')
    {
        target -= 'A';
        return bitmaps_5x7_A_Z[target];
    }
#endif // USE_UPPERCASE_5x7

#ifdef USE_LOWERCASE_5x7
    if (target >= 'a' && target <= 'z')
    {
        target -= 'a';
        return bitmaps_5x7_a_z[target];
    }
#endif // USE_LOWERCASE_5x7

    else if (target == ' ')
    {
        return &bitmap_5x7_space[0][0];
    }
    else if (target >= '!' && target <= '&')
    {
        target -= '!';
        return bitmaps_5x7_symbols1[target];
    }
    else // either unsupported or an actual question mark :)
    {
        return &bitmap_5x7_questionmark[0][0];
    }
}
