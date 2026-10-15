// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
int func_002715F8(char *s);
unsigned short FUN_001b5b58(unsigned char ch);
void func_00238308(char *s, unsigned short *pw)
{
    int i;
    int c = func_002715F8(s);
    for (i = 0; i < c; i++) {
        unsigned short w = FUN_001b5b58(s[i]);
        unsigned short lo = w & 0xFF;
        unsigned short hi = (w >> 8) & 0xFF;
        pw[i] = (lo << 8) | hi;
    }
    pw[i] = 0;
}
