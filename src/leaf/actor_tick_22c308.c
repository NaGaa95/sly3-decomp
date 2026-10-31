// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_AS: gnu-2.9
// Actor tick (sibling of func_001AD7F0): base tick, per-state update of the animation blocks, then expire the linked target when it
// has been stale for 0.1s or lost its component.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VTE { short delta; short pad; void *pfn; };
struct LO { unsigned char pad0[0xC]; struct VTE *pvt; };
struct BITS { unsigned char pad0[0x28]; unsigned long :56; unsigned long f : 8; };
struct Link { unsigned char pad0[0x14]; void **target; };
#define F(T, o) (*(T *)((char *)p + (o)))
#define A(o) ((char *)p + (o))
extern unsigned char D_00475480[];
extern float D_0036BB98;
void func_00152A48(void *p);
void func_0022C500(void *p);
void func_0022C698(void *p);
void func_0024E878(void *p, float g);
void func_00258CF0(void *p, float g);
void func_00258DA0(void *p);
void func_001B9C48(void *p);
void func_001B30E8(void *p);
void func_001C2B48(void *p);
void *func_00156AB0(void *p);
qword func_0024F278(void *actor, void *animation, float g);
void func_0022C570(void *p);
int func_0013B500(void *object, int identifier);
int func_0013C658(void *game, void *first, void *second);
void func_0013CD10(void *game, void *owner);
static __inline__ qword VMulX(qword a, qword s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s)); return r; }
static __inline__ qword VuFloat(float g) { qword r; __asm__("qmtc2 %1, %0" : "=j"(r) : "r"(g)); return r; }
void func_0022C308(char *p)
{
    VU u;
    func_00152A48(p);
    if (!(((struct BITS *)p)->f & 1))
        return;
    func_0022C500(p);
    func_0022C698(p);
    switch (F(int, 0x1470)) {
    case 0:
        ((void (*)(void *))((struct LO *)p)->pvt[0x6E].pfn)(p + ((struct LO *)p)->pvt[0x6E].delta);
        break;
    case 1: {
        char *block = A(0x1480);
        func_0024E878(p, F(float, 0x110C));
        func_00258CF0(block, 1.0f);
        func_00258DA0(block);
        break;
    }
    case 2: {
        char *block = A(0x1530);
        func_0024E878(p, F(float, 0x110C));
        func_00258CF0(block, ((float *)F(void *, 0x134))[2]);
        func_00258DA0(block);
        break;
    }
    case 3:
        func_001B9C48(A(0x320));
        break;
    case 4:
        func_001B30E8(A(0x500));
        break;
    case 5:
        func_001C2B48(A(0xE40));
        break;
    case 8: {
        void *animation = func_00156AB0(p);
        qword s;
        qword v = func_0024F278(p, animation, ((float *)animation)[7]);
        s = VuFloat(-1.0f);
        u.q = s;
        F(qword, 0x1A0) = VMulX(v, s);
        break;
    }
    case 6: case 7:
    default:
        break;
    }
    func_0022C570(p);
    if (F(void *, 0x15F0)) {
        if (F(float, 0x15F4) + 0.1f < D_0036BB98) {
            if (!func_0013B500(*F(struct Link *, 0x15F0)->target, 0x2F)) {
                F(void *, 0x15F0) = 0;
            } else {
                void *content = *(void **)((char *)*F(struct Link *, 0x15F0)->target + 0xDC);
                if (!content)
                    F(void *, 0x15F0) = 0;
                else if (!func_0013C658(D_00475480, F(void *, 0xDC), content))
                    F(void *, 0x15F0) = 0;
            }
            if (!F(void *, 0x15F0))
                func_0013CD10(D_00475480, p);
        }
    }
}
