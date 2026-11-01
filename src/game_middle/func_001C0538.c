// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Commit a candidate list entry. Without a supplied entry the actor's list is searched (func_001C0B70); no hit starts the
// state-dependent fallback action (func_00240CB0 with a mask chosen from the state). A hit on the current player is
// accepted when the aim test passes; the selected entry is then reported, and for the listed kinds the entry's virtual
// pick-up query feeds the tracker. Otherwise the entry is copied into the actor and its start sound/animation request is made.
typedef int qword __attribute__((mode(TI)));
typedef struct VT { short d; short pad; void *pfn; } VT;
typedef struct Entry { int x0; int x4; int x8; int xc; qword x10; } Entry;
struct Pos { char pad[0x70]; qword x70; };
struct Axis { char pad[0x80]; qword x80; };
struct Obj { char pad0[0xC]; VT *vt; char pad10[0x28 - 0x10]; unsigned long flags; };
struct P {
    char pad0[0x48]; struct Pos *x48;
    char pad4C[0xD8 - 0x4C]; struct Axis *xD8;
    char padDC[0x320 - 0xDC]; char x320[0x4D0 - 0x320];
    qword x4D0; qword x4E0;
    char pad4F0[0xA20 - 0x4F0]; char list[0xE44 - 0xA20];
    int xE44;
};
struct G { char pad[0x4FA4]; int x4FA4; };
extern struct G D_00475480;
extern qword D_00317560;
int func_001C0B70(void *list, Entry *out, int mode);
void *func_001F4AD0(struct G *g, int n);
qword func_001C03A0(struct P *p, Entry *e, float g);
float func_001B83F0(qword delta, qword axis, float a, float b, float c, float d);
void func_001C11E0(void *list, Entry *e);
void func_001B7268(void *context, int kind, int a, int b, float gain);
int func_0013B500(int id, int kind);
void func_0015BBB8(struct G *g, int a);
void func_001BBCA8(void *context, int id);
void func_00240CB0(void *self, int a, void *target, int mask, int c, int d, qword e, qword f, int g);
static inline qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_001C0538(struct P *p, Entry *q)
{
    Entry e;
    if (!q) {
        if (!func_001C0B70(p->list, &e, 0)) {
            int mask;
            switch (p->xE44) {
            case 5: mask = 0x4000; break;
            case 3: mask = 0x2000; break;
            case 2: mask = 0x1000; break;
            default: mask = 0x800; break;
            }
            func_00240CB0(p, 0, p, mask, 10, 1, D_00317560, D_00317560, 0);
            return;
        }
        q = &e;
        if (!D_00475480.x4FA4 && p == func_001F4AD0(&D_00475480, 0)) {
            qword r = func_001C03A0(p, &e, 0.0f);
            float g = func_001B83F0(VSub(r, p->x48->x70), p->xD8->x80, 1000.0f, -1000.0f, 1.0f, -1.0f);
            if (1.25f < g) {
                func_001C11E0(p->list, &e);
                func_001B7268(p->x320, 0xB, 0, 0, 1.0f);
                if (e.x4) {
                    if (func_0013B500(e.x0, 0x26) || func_0013B500(e.x0, 0xA) || func_0013B500(e.x0, 0xC) ||
                        func_0013B500(e.x0, 0x25) || func_0013B500(e.x0, 0xB) || func_0013B500(e.x0, 0x20) ||
                        func_0013B500(e.x0, 0x24)) {
                        struct Obj *o = (struct Obj *)e.x0;
                        func_0015BBB8(&D_00475480,
                                      (o->flags & 0x1000000000000000UL)
                                          ? ((int (*)(void *))o->vt[26].pfn)((char *)o + o->vt[26].d)
                                          : 0);
                        func_001BBCA8(p->x320, e.x0);
                    }
                }
                return;
            }
        }
    }
    p->x4D0 = *(qword *)q;
    p->x4E0 = q->x10;
    func_001B7268(p->x320, 0xA, 0, 0, 1.0f);
}
