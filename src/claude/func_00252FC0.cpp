// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct BITS { unsigned char ab[16]; };
struct VTE { short d; short pad; void (*pfn)(void *, int, int, int, void *, int); };
struct VT { char pad[0x18]; VTE e18; };
struct VTE2 { short d; short pad; void (*pfn)(void *); };
struct VT2 { char pad[0x1B0]; VTE2 e1B0; };
struct SO2 { char pad[0xC]; VT2 *pvt; };
struct SO { char pad[0xC]; VT *pvt; char pad10[0x168 - 0x10]; SO2 *p168; char pad16C[0x2F0 - 0x16C]; int n2F0; BITS grf; };
struct ARGS { int *pn; int *pm; };
extern "C" {
extern char D_0036C700[];
BITS func_00252AD0(int n);
void func_00252DE0(SO *p, BITS grf);
void func_001854C8(void *table, int kind, void *link);
void func_00252FC0(SO *p, int n);
}
static inline BITS operator~(const BITS &a)
{
    BITS r;
    for (int i = 0; i < 16; i++) r.ab[i] = ~a.ab[i];
    return r;
}
static inline BITS operator&(const BITS &a, const BITS &b)
{
    BITS r;
    for (int i = 0; i < 16; i++) r.ab[i] = a.ab[i] & b.ab[i];
    return r;
}
void func_00252FC0(SO *p, int n)
{
    BITS bits = func_00252AD0(n);
    func_00252DE0(p, p->grf & ~bits);
    int m = -1;
    ARGS args;
    args.pn = &m;
    args.pm = &n;
    p->pvt->e18.pfn((char *)p + p->pvt->e18.d, 7, 0, 2, &args, 0);
    switch (n) {
    case 3:
        func_001854C8(D_0036C700, 0x15, p);
        break;
    case 0x12:
        func_001854C8(D_0036C700, 0x17, p);
        break;
    case 0x44:
        if (p->n2F0 == 2 && p->p168)
            p->p168->pvt->e1B0.pfn((char *)p->p168 + p->p168->pvt->e1B0.d);
        break;
    }
}
