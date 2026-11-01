// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-state reaction of the actor to the contact record px (same routine as Sly 2 func_001B9130): after the base update,
// dispatches on the actor state to the matching component or contact test.
typedef int qword __attribute__((mode(TI)));
typedef struct VTE { short d; short pad; void (*pfn)(); } VTE;
typedef struct Q { char pad[0xC]; VTE *vt; } Q;
typedef struct X {
    char pad0[0xC];
    Q *pq;
    char pad10[0x80 - 0x10];
    qword x80;
    char pad90[0x10 - 0x8 + 0x88 - 0x90 + 0x8];
} X;
typedef struct P {
    char pad0[0xC];
    VTE *vt;
    char pad10[0xE40 - 0x10];
    char xE40[0x1010 - 0xE40];
    char x1010[0x1520 - 0x1010];
    int x1520;
    int pad1524;
    int x1528;
    char pad152C[0x1534 - 0x152C];
    char x1534[0x18C0 - 0x1534];
    int x18C0;
    char pad18C4[0x18D8 - 0x18C4];
    int x18D8;
    char pad18DC[0x1AD4 - 0x18DC];
    int x1AD4;
    char pad1AD8[0x1B18 - 0x1AD8];
    float x1B18;
} P;
extern "C" float D_00349880[];
extern "C" char D_00475480[];
extern "C" void func_0024E400(P *p, X *px, int i);
extern "C" void func_001C3D18(void *p, X *px, int i);
extern "C" void func_001BFA08(void *p, X *px, int i);
extern "C" qword func_00120D98(qword a, qword b);
extern "C" int func_001CDD78(void *g, X *px);
extern "C" void func_001CDD30(void *g, int r, void *p);

extern "C" void func_001E1A68(P *p, X *px, int i)
{
    int n;
    func_0024E400(p, px, i);
    switch (p->x1520) {
    case 15:
        func_001C3D18(p->xE40, px, i);
        break;
    case 13:
        n = p->x18C0;
        if (n == 1) {
            Q *pq = *(Q **)((char *)px + ((n - i) << 6) + 0xC);
            if (((int (*)(void *))pq->vt[66].pfn)((char *)pq + pq->vt[66].d)) {
                if (*(float *)((char *)px + 0x88) < 0.7f) {
                    qword v = ((qword (*)(void *))p->vt[38].pfn)((char *)p + p->vt[38].d);
                    qword r = func_00120D98(v, px->x80);
                    float g;
                    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(r));
                    if (g < -0.3f) p->x18D8 = n;
                }
            }
        }
        break;
    case 3:
        if (p->x1528 == 1) {
            if (D_00349880[i] * *(float *)((char *)px + 0x88) > 0.7f) {
                func_001CDD30(D_00475480, func_001CDD78(D_00475480, px), p->x1534);
            }
        }
        break;
    case 21:
        func_001BFA08(p->x1010, px, i);
        break;
    case 22:
        if (p->x1AD4 == 2) {
            *(int *)((char *)px + 0x94) = 0;
        } else {
            *(int *)((char *)px + 0x98) = 0;
            *(float *)((char *)px + 0x94) = (1.0f - p->x1B18) * 0.6f + p->x1B18;
        }
        break;
    }
}
