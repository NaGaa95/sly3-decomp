// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern unsigned char D_0031F0D0[];
extern unsigned char D_0032A691[];
extern "C" unsigned int func_0011BF50(unsigned char *text)
{
    if (!text) text=D_0031F0D0;
    unsigned int hash=0;
    while (*text) {
        int c=*text;
        int upper=(D_0032A691[c]&2)?c-32:c;
        ++text;
        hash=hash*33+upper;
    }
    return hash;
}
