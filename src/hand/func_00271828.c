// Original Sly3 game-text append:16-bit destination and mapped unsigned source bytes.
// Algorithm is anchored by full original caller/helper evidence and the admitted2717E0 conversion loop.
// SLY3_CFLAGS: -Os -G0
extern const unsigned short D_00349D88[256];
int func_00271700(const unsigned short *text);

unsigned short *func_00271828(unsigned short *destination,const char *text)
{
    const unsigned char *source=(const unsigned char *)text;
    unsigned short *output=destination+func_00271700(destination);
    while(*source)
        *output++=D_00349D88[*source++];
    *output=0;
    return destination;
}
