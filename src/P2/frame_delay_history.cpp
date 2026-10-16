// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
extern char D_0036C698[];
extern int D_0036C694, D_0036C674, D_0036C690;
extern volatile unsigned int D_0036DCA8;
extern const int D_00344FBC, D_00344FC0;
}
extern "C" int func_00183038(unsigned int frameStart)
{
    int index=D_0036C694;
    int *slot=((int *)D_0036C698)+index;
    if (*slot>=2)
        --D_0036C674;
    *slot=(int)(D_0036DCA8-frameStart);
    if (*slot>=2)
        ++D_0036C674;
    D_0036C694=(unsigned int)(index+1)%15;
    int enabled;
    if (D_0036C690)
        enabled=D_0036C674>=D_00344FC0;
    else
        enabled=D_0036C674>=D_00344FBC;
    D_0036C690=enabled;
    return enabled;
}
