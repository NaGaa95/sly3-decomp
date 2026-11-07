// Sly 2 counterpart: _sceCd_cd_read_intr (decomp src/lib/_sceCd_cd_read_intr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int size1; int size2; char *dst1; char *dst2; char buf1[0x40]; char buf2[0x40]; } FixAlign;
extern char _sceCd_mode[];
void func_0029FEC8(void *);
void func_0029FF70(void *data)
{
    FixAlign *p = (FixAlign *)((unsigned int)data | 0x20000000);
    int i;
    if (p->size1 > 0) {
        char *d = p->dst1;
        char *du = (char *)((unsigned int)d | 0x20000000);
        for (i = 0; i < p->size1; i++) {
            d[i] = du[i] = p->buf1[i];
        }
    }
    if (p->size2 > 0) {
        char *d = p->dst2;
        char *du = (char *)((unsigned int)d | 0x20000000);
        for (i = 0; i < p->size2; i++) {
            d[i] = du[i] = p->buf2[i];
        }
    }
    func_0029FEC8(_sceCd_mode);
}
