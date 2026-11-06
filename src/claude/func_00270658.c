// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of the Sly 2 source src/hand/func_0021E0D8.c (ChDigitFromG).
extern unsigned char D_00349D70[];
double func_002A38B8(double, double);
double func_0011EC60(double);
double func_0029C488(double,double);
double func_0029C420(double,double);
double func_0029CA00(int);
int func_0029CAB8(double);
/* Digit of g at decimal position a (precision b): 0 outside [b, b+15). */
unsigned char func_00270658(double g, int a, int b)
{
int i; double x;
    if (a < b || a - 15 >= b) i = 0;
    else {
        x = func_0011EC60(func_0029C488(g, func_002A38B8(10.0, func_0029CA00(-b))));
        i = func_0029CAB8(func_0029C420(x, func_0029C488(func_0011EC60(func_0029C488(x, 0.1)), 10.0)));
    }
    return D_00349D70[i];
}
