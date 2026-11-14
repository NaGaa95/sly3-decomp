// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct M3 { qword r[3]; };
struct PO { char pad[0x70]; qword pos; };
struct E { struct PO *po; char pad[0x14]; float x18, x1C; qword pos; qword top; qword bottom; char pad1[0x10]; };
struct S { char pad[0x190]; struct E ae[4]; char pad1[0x36C - 0x310]; struct M3 *pm; void *task; char pad2[0x380 - 0x374]; struct M3 m; int x3B0; };
extern char D_0034A070[];
extern int D_003292D8[4];
extern struct { qword q; } D_00317550;
extern "C" {
void func_001F3BF8(struct S *p);
void func_001C8970(struct S *p, int k, void *pv, int n);
void *func_0023DDA0(void *owner, int identity, int kind);
qword func_001C9428(void *a, void *b, qword q);
qword func_0011D3C0(struct M3 *pm);
void *func_00130078(void *owner, void *channel, int a, int b, int c, qword value);
void func_0027C860(struct S *p, int k);
void func_001F4670(struct S *p, int k);
void func_00279F00(struct S *p);
}
/* VU_FLOAT by value: fresh temp per call keeps both 0(sp) home stores */
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j,!r"(q) : "r,m"(f)); } };
static inline qword AddScaled(qword a, qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s.q));
    return r;
}
void func_00279F00(struct S *p)
{
    unsigned int i;
    func_001F3BF8(p);
    func_001C8970(p, 3, D_0034A070, 0);
    for (i = 0; i < 4; i++) {
        struct E *e = &p->ae[i];
        qword pos;
        e->po = (struct PO *)func_0023DDA0(p, D_003292D8[i], 0xD);
        pos = func_001C9428(0, p, e->po->pos);
        __asm__("qmtc2.ni %1, %0" : "=j"(pos) : "r"(pos));
        e->pos = pos;
        e->top = AddScaled(pos, D_00317550.q, VU_FLOAT(e->x1C));
        e->bottom = AddScaled(pos, D_00317550.q, VU_FLOAT(e->x18));
    }
    p->pm = (struct M3 *)func_0023DDA0(p, 0x22, 6);
    if (p->pm) {
        p->m = *p->pm;
        p->task = func_00130078(p, p->pm, 0, 0x13, 3, func_0011D3C0(&p->m));
    }
    p->x3B0 = -1;
    func_0027C860(p, 0);
    func_001F4670(p, 1);
}
