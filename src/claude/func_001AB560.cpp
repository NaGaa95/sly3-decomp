// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00189EC8).
typedef int qword __attribute__((mode(TI)));
struct HIT { qword v0; char pad[0x28 - 0x10]; float g28; char pad1[0x40 - 0x2C]; float g40; char pad2[0x60 - 0x44]; };
struct CTX { CTX(); ~CTX(); char pad[0x10]; };
struct M { char pad[0x4]; int x4; char pad1[0x10 - 0x8]; qword v10; char pad2[0x30 - 0x20]; qword v30; qword v40; qword v50;
    char pad3[0x08]; float g48; };
struct O { char pad[0xDC]; int xDC; char pad1[0x218 - 0xE0]; int x218; };
extern "C" {
qword func_001C9428(void *p, void *q, qword v);
void func_0025CF18(void *pv, qword vMin, qword vMax, void *pfn, int n, int *pn0, int *pn1);
int func_00165000(int n, qword a, qword b, int n0, int n1, HIT *phit);
void func_0012FE90(void *p, qword v);
void func_0025CDD0();
extern char D_00475480[];
extern qword D_00317550;
extern qword D_00317560;
int func_001AB560(O *p, M *pm, void *px);
}
static inline qword VMin(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword VMax(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
int func_001AB560(O *p, M *pm, void *px)
{
    if (pm->x4) {
        HIT hit;
        CTX ctx;
        union { qword q; } u;
        int n0, n1;
        qword a, b, c;
        a = func_001C9428(p, 0, pm->v30);
        b = func_001C9428(p, 0, pm->v40);
        c = func_001C9428(p, 0, pm->v50);
        func_0025CF18(D_00475480, VMin(a, VMin(b, c)), VMax(a, VMax(b, c)), (void *)func_0025CDD0, p->xDC, &n0, &n1);
        if ((func_00165000(0, a, b, n0, n1, &hit) || func_00165000(0, b, c, n0, n1, &hit)) &&
            hit.g40 != 0.0f && 0.7f < hit.g28) {
            qword w;
            hit.v0 = VSub(hit.v0, D_00317550);
            w = func_001C9428(0, p, hit.v0);
            u.q = w;
            func_0012FE90(px, VSub(w, pm->v10));
            return 1;
        } else {
            func_0012FE90(px, D_00317560);
            if (p->x218 && ((float *)&pm->v40)[2] < -85.0f)
                return 0;
            return 1;
        }
    }
    return 1;
}
