// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct LO;
struct VEntry { short delta; short pad; void *fn; };
struct LO { char pad[0xC]; struct VEntry *table; char pad2[0x260 - 0x10]; qword v260; };
struct S { char pad[0x10]; struct LO *plo; char pad2[0x60 - 0x14]; qword v60; };
extern struct LO *D_00370AC0;
extern qword D_00317550;
float func_001205C8(qword v);
M3 func_0011C8C0(float g, qword v);
void *func_001F4A80(struct LO *p);
void func_00166548(void *p);
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
#define VFN(o, i, T) ((T)(o)->table[i].fn)
#define VTHIS(o, i) ((char *)(o) + (o)->table[i].delta)
void func_0015FBD8(struct S *p)
{
    void *q;
    struct LO *plo = p->plo;
    VFN(plo, 34, void (*)(void *, qword))(VTHIS(plo, 34), Sub(p->v60, plo->v260));
    if (D_00370AC0) {
        qword pos = *(qword *)((char *)VFN(D_00370AC0, 36, void *(*)(void *))(VTHIS(D_00370AC0, 36)) + 0x30);
        M3 m = func_0011C8C0(func_001205C8(Sub(pos, p->v60)), D_00317550);
        VFN(p->plo, 35, void (*)(void *, M3 *))(VTHIS(p->plo, 35), &m);
    }

    q = func_001F4A80(p->plo);
    if (q)
        func_00166548(q);
}
