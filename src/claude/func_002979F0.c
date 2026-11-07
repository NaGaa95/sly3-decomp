// Sly 2 counterpart: _lf_bind (decomp src/lib/_lf_bind.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int pad[9]; void *serve; } ClientData;
typedef struct { char c[4]; } B4;
extern int D_0034A6B8;
extern ClientData D_004CCBC0;
extern B4 D_004CC9C0;
extern B4 D_004CCBE8;
int func_00295D28(ClientData *, unsigned int, unsigned int);
int func_00295F08(ClientData *, int, unsigned int, void *, int, void *, int, void *, void *);
int func_002979F0(void)
{
    int i;
    if (D_0034A6B8 < 0) {
    again:
        if (func_00295D28(&D_004CCBC0, 0x80000006, 0) < 0)
            return -1;
        if (D_004CCBC0.serve != 0) {
            D_0034A6B8 = 0;
            if (func_00295F08(&D_004CCBC0, 0xFF, 0, 0, 0, &D_004CC9C0, 4, 0, 0) < 0)
                return 0xFFFEFFFF;
            D_004CCBE8 = D_004CC9C0;
            return 0;
        }
        i = 0x100000;
        do __asm__ volatile(""); while (i-- != 0);
        goto again;
    }
    return 0;
}
