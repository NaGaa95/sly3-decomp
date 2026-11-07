// Sly 2 counterpart: mceIntrReadFixAlign (decomp src/lib/mceIntrReadFixAlign.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int size1; int size2; char *dst1; char *dst2; char buf1[0x40]; char buf2[0x40]; } FixAlign;
extern int D_0034DF98;
int func_002936D0(int);
void func_002A2708(void *data)
{
    FixAlign *p = (FixAlign *)((unsigned int)data | 0x20000000);
    int i;
    char *d, *du;
    if (p->size1) {
        d = p->dst1;
        du = (char *)((unsigned int)d | 0x20000000);
        for (i = 0; i < p->size1; i++) {
            *du++ = *d++ = p->buf1[i];
        }
    }
    if (p->size2) {
        d = p->dst2;
        du = (char *)((unsigned int)d | 0x20000000);
        for (i = 0; i < p->size2; i++) {
            *du++ = *d++ = p->buf2[i];
        }
    }
    func_002936D0(D_0034DF98);
}
