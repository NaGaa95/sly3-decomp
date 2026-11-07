// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00280F70: vertical hit span query (Sly 3 version of Sly 2 func_00229468, rewritten without pins).
typedef int qword __attribute__((mode(TI)));
typedef struct MSG { int cb; int cbAlign; } MSG;
typedef struct MARK { int a; } MARK;
struct LSG { char pad[0x10]; qword pos; char pad1[0x10]; qword normal; float g40; float g44; char pad2[0x18]; };
struct L { char pad[0xD0]; int xD0; };
extern qword D_00317550;
extern qword D_00317560;
void func_001D2770(MARK *pm);
void func_001D2798(MARK *pm, int n);
void *func_001D25B0(MSG *pmsg);
int func_00281850();
int func_002414D8(struct L *pl, int (*pfn)(), int n, void **apv);
int func_00165130(qword a, qword b, int cso, void **apso, int cMax, struct LSG *alsg);
int func_0011E9F0(float a, float b, float eps);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static inline int WordY(qword q){int r;__asm__("prot3w %0,%1":"=r"(r):"r"(q));return r;}
static inline int WordZ(qword q){int r;__asm__("pextuw %0,$0,%1":"=r"(r):"r"(q));return r;}
static inline float FloatWord(int word){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static __inline__ float Eps(void) { float e = 0.0001f; __asm__("" : "+f"(e)); return e; }
static inline int NearX(qword d,qword n){return func_0011E9F0(GetX(d),GetX(n),Eps());}
static inline int NearY(qword d,qword n){int y=WordY(d);float e=Eps();return func_0011E9F0(FloatWord(y),GetY(n),e);}
static inline int NearZ(qword d,qword n){int z=WordZ(d);float e=Eps();return func_0011E9F0(FloatWord(z),GetZ(n),e);}
float func_00280F70(struct L *p, qword a, qword b, qword *ppos, qword *pnormal)
{
    struct { MARK mark __attribute__((aligned(16))); MSG msg __attribute__((aligned(16))); struct LSG alsg[1]; } w;
    void **apv;
    int c;
    float g;
    func_001D2770(&w.mark);
    {
        MSG *pm = &w.msg;
        pm->cb = p->xD0 * 4;
        pm->cbAlign = 0x10;
        apv = (void **)func_001D25B0(pm);
    }
    c = func_002414D8(p, func_00281850, 0, apv);
    if (!func_00165130(a, b, c, apv, 1, w.alsg)) {
        if (pnormal)
            *pnormal = D_00317550;
        func_001D2798(&w.mark, 2);
        return 0.0f;
    }
    if (ppos)
        *ppos = w.alsg[0].pos;
    if (pnormal) {
        qword n = w.alsg[0].normal;
        qword d;
        int f;
        *pnormal = n;
        d = D_00317560;
        f = NearX(d, n) && NearY(d, n) && NearZ(d, n);
        if (f)
            *pnormal = D_00317550;
    }
    g = w.alsg[0].g44 - w.alsg[0].g40;
    func_001D2798(&w.mark, 2);
    return g;
}
