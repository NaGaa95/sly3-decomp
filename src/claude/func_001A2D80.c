// SLY3_CFLAGS: -Os -G0
typedef struct S {
    char pad0[0x10];
    char *pb;      /* 0x10 */
    int cb;        /* 0x14 */
    char pad18[0x34 - 0x18];
    int cbSpool;   /* 0x34 */
    char *abSpool; /* 0x38 */
    int pad3c;
    int x40;
    int x44;
    int x48;
    int x4c;
    int x50;
    int x54;
    int x58;
    int x5c;
    int x60;
} S;

extern int func_002A0E08(void);
extern int func_002A0480(int);
extern int func_002A10D8(void);
extern void func_001630B0(int isector, int csector, void *pv, int mode);

static __inline__ int Min(int a, int b) { return a < b ? a : b; }
void func_001A2D80(S *p)
{
    int cbuf;
    int n;
    int c54;

    p->pb += p->cb;
    p->cb = 0;
    c54 = p->x54;
    cbuf = p->cbSpool / c54;

    if (cbuf > 0x8000) cbuf &= -0x8000; else cbuf &= -0x800;

    if (p->x58 > 0) {
        n = p->x5c + 1;
        if (p->pb == p->abSpool + n * cbuf) {
            p->x5c = n % c54;
            p->x58--;
            p->pb = p->abSpool + p->x5c * cbuf;
        }
    }

    do {
        if (p->x44 > 0) {
            int t = Min(func_002A0E08() + p->x4c, p->x44);
            if (p->x40 < t) {
                p->x40 = t;
            } else if (func_002A0480(1) == 0) {
                if (func_002A10D8() == 0) {
                    int c = p->x44;
                    p->x40 = c;
                    p->x50 += c / 0x800;
                    p->x48 -= c;
                    p->x44 = 0;
                    p->x4c = 0;
                } else {
                    int c = p->x40;
                    register int index __asm__("$7") = p->x60; /* the one pin: index in $a3 */
                    char *buffer = p->abSpool + index * cbuf + c;
                    int count = (p->x44 - c + 0x7FF) >> 11;
                    int sector = p->x50 + c / 0x800;
                    p->x4c = c;
                    func_001630B0(sector, count, buffer, 0);
                }
            }
        }

        if (p->x58 < p->x54 && p->x44 == 0 && p->x48 > 0) {
            int c = Min(p->x48, cbuf);
            int c7; int k; char *ab;
            ab = p->abSpool;
            c7 = c + 0x7FF;
            k = p->x58 + 1;
            /* zero-insn tie: c7 waits for k (orders sw/sra before the 4th-arg li) */
            __asm__("" : "=r"(c7) : "0"(c7), "r"(k));
            p->x40 = 0;
            p->x44 = c;
            p->x60 = (p->x60 + 1) % p->x54;
            p->x58 = k;
            func_001630B0(p->x50, c7 >> 11, ab + p->x60 * cbuf, 0);
        }

        if (p->x58 == 0) {
            p->cb = 0;
        } else {
            int c = (p->x58 == 1) ? p->x40 : cbuf;
            int v = c - (p->pb - (p->abSpool + p->x5c * cbuf));
            p->cb = Min(v, 0x1000);
        }
    } while (p->cb == 0 && p->x48 > 0);
}
