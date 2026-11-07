// Sly 2 counterpart: sceSifRebootIop (decomp src/lib/sceSifRebootIop.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern char D_0032ACC0[];
extern char D_0032ACD0[];
int func_002955E0(const char *, ...);
void func_002956E0(int);
void func_00295880(void);
int func_00297E18(const char *, int);
int func_00297FC0(const char *img)
{
    char param[80];
    char *s = D_0032ACC0;
    register char *d asm("$3");
    register int check asm("$2");
    int byte;
    const char *p = img;
    unsigned int origin;
    if (*p) {
        origin = (unsigned int)img - 11;
        do { ++p; } while (*p);
    } else {
        origin = (unsigned int)img - 11;
    }
    if ((unsigned int)p - origin > 80) {
        func_002955E0(D_0032ACD0, img);
        return 0;
    }
    func_002956E0(0);
    func_00295880();
    {
        register char *q asm("$3") = param;
        while ((check = *s) != 0)
            *q++ = *s++;
        d = q;
    }
    byte = (unsigned char)*img;
    if (byte) do {
        *d++ = byte;
        check = *++img;
        byte = check;
    } while (check);
    *d = 0;
    return func_00297E18(param, 0);
}
