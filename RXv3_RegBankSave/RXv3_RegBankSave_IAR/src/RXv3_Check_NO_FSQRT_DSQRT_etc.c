#include <math.h>

#if defined(__CCRX__)
// Use -library=function option for this source file.
// Use -nouse_div_inst option for this source file.
// Don't use -tfu=intrinsic,mathlib option for this file.
#elif defined(__ICCRX__)
// Use --sqrt_must_set_errno option for this source file.
// Don't use --tfu intrinsic_mathlib option for this source file.
#elif defined(__GNUC__)
// Don't use -mrxv2-fsqrt option for this source file.
// Don't use -mtfu=intrinsic,mathlib option for this source file.
#endif
// Be aware that some RXv3 MCUs don't have all features of RXv3 as follows.
//                      RX66T RX66N RX671 RX660 RX72T RX72N RX72M
// Max Operating MHz    160   120   120   120   200   240   240
// Register Bank Save   x     o     o     o     o     o     o
// DPFPU                x     o     o     x     x     o     o
// TFU                  x     x     x     o     o     o     o

static double Check_Not_Using_DSQRT(double x);
static double Check_Not_Using_DSQRT(double x)
{
    return sqrt(x);  // DSQRT is used in library.
}

static float Check_Not_Using_FSQRT(float x);
static float Check_Not_Using_FSQRT(float x)
{
    return sqrtf(x); // FSQRT is used in library.
}

void *m_debug_Check_Not_Using_DSQRT = (void *)Check_Not_Using_DSQRT;
void *m_debug_Check_Not_Using_FSQRT = (void *)Check_Not_Using_FSQRT;

extern double d1, d2;
extern float f1, f2;

#if defined(__CCRX__)

static void Check_Not_Using_DDIV(void);
static void Check_Not_Using_DDIV(void)
{
    d2 = d1 / d2;
}

static void Check_Not_Using_FDIV(void);
static void Check_Not_Using_FDIV(void)
{
    f2 = f1 / f2;
}

void *m_debug_Check_Not_Using_DDIV = (void *)Check_Not_Using_DDIV;
void *m_debug_Check_Not_Using_FDIV = (void *)Check_Not_Using_FDIV;

#endif

void Check_Not_Using_DSQRT_FSQRT(void);
void Check_Not_Using_DSQRT_FSQRT(void)
{
    ((double (*)(double))m_debug_Check_Not_Using_DSQRT)(4.0);
    ((float (*)(float))m_debug_Check_Not_Using_FSQRT)(4.0);
}

extern double dA, dB, dC, dD;
static void Check_DPUSHM_DPOPM(void);
static void Check_DPUSHM_DPOPM(void)
{
    double d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, d16;

    d3  = d1 + d2 +  3.0;
    d4  = d1 - d2 +  4.0;
    d5  = d1 + d2 +  5.0;
    d6  = d1 - d2 +  6.0;
    d7  = d1 + d2 +  7.0;
    d8  = d1 - d2 +  8.0;
    d9  = d1 + d2 +  9.0;
    d10 = d1 - d2 + 10.0;
    d11 = d1 + d2 + 11.0;
    d12 = d1 - d2 + 12.0;
    d13 = d1 + d2 + 13.0;
    d14 = d1 - d2 + 14.0;
    d15 = d1 + d2 + 15.0;
    d16 = d1 - d2 + 16.0;

    dA = d3 + d4 + d5 + d6 + d7 + d8 + d9 + d10 + d11 + d12 + d13 + d14 + d15 + d16;
    dB = d3 * d4 * d5 * d6 * d7 * d8 * d9 * d10 * d11 * d12 * d13 * d14 * d15 * d16;
    dC = d3 - d4 - d5 - d6 - d7 - d8 - d9 - d10 - d11 - d12 - d13 - d14 - d15 - d16;
    dD = d3 / d4 / d5 / d6 / d7 / d8 / d9 / d10 / d11 / d12 / d13 / d14 / d15 / d16;
}

void *m_debug_N_Check_DPUSHM_DPOPM = (void *)Check_DPUSHM_DPOPM;

static float Check_TFU_sinf(float x);
static float Check_TFU_sinf(float x)
{
    return sinf(x);
}

static float Check_TFU_cosf(float x);
static float Check_TFU_cosf(float x)
{
    return cosf(x);
}

static float Check_TFU_atan2f(float y, float x);
static float Check_TFU_atan2f(float y, float x)
{
    return atan2f(y, x);
}

static float Check_TFU_hypotf(float x, float y);
static float Check_TFU_hypotf(float x, float y)
{
    return hypotf(x, y);
}

static float Check_TFU_asinf(float x);
static float Check_TFU_asinf(float x)
{
    return asinf(x);
}

static float Check_TFU_acosf(float x);
static float Check_TFU_acosf(float x)
{
    return acosf(x);
}

static float Check_TFU_atanf(float x);
static float Check_TFU_atanf(float x)
{
    return atanf(x);
}

static float Check_TFU_tanf(float x);
static float Check_TFU_tanf(float x)
{
    return tanf(x);
}

void *m_debug_N_Check_TFU_sinf   = (void *)Check_TFU_sinf;
void *m_debug_N_Check_TFU_cosf   = (void *)Check_TFU_cosf;
void *m_debug_N_Check_TFU_atan2f = (void *)Check_TFU_atan2f;
void *m_debug_N_Check_TFU_hypotf = (void *)Check_TFU_hypotf;
void *m_debug_N_Check_TFU_asinf  = (void *)Check_TFU_asinf;
void *m_debug_N_Check_TFU_acosf  = (void *)Check_TFU_acosf;
void *m_debug_N_Check_TFU_atanf  = (void *)Check_TFU_atanf;
void *m_debug_N_Check_TFU_tanf   = (void *)Check_TFU_tanf;
