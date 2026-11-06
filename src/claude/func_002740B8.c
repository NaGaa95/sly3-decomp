// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct VTE { short d; short pad; struct XF *(*pf)(void *); };
struct O { int a[3]; struct VTE *vt; char pad10[0x218 - 0x10]; int x218; char pad21c[0x29C - 0x21C]; char a29C[0x33C - 0x29C]; int x33C;
           char pad340[0x10D4 - 0x340]; int x10D4; };
struct CM { char pad[0x2F4]; int x2F4; char pad2f8[0x30C - 0x2F8]; int x30C; };
struct SW { char pad[0x3EB8]; int c; struct CM *apcm[5]; };
struct S { char pad[0x104]; void *x104; char pad108[0x120 - 0x108]; int x120; };
extern struct SW D_00475480;
struct O *func_00166540(struct CM *pcm);
int func_00273F68(struct S *p, struct CM *pcm, struct O *o);
int func_0013B500(void *pj, int k);
void *func_002387A8(void *pv, int k);
qword func_001C9428(void *a, void *b, qword q);
struct BSP *func_00119C90(void *p, unsigned int limit, qword q);
void func_00166150(struct CM *pcm, struct S *p);
void func_00166228(struct CM *pcm, struct S *p);
static inline struct XF *Xf(struct O *o) { return o->vt[36].pf((char *)o + o->vt[36].d); }
void func_002740B8(struct S *p)
{
    int i;
    for (i = 0; i < D_00475480.c; i++) {
        struct CM *pcm = D_00475480.apcm[i];
        struct O *o = func_00166540(pcm);
        int r;
        if (pcm->x30C || !o)
            continue;
        r = func_00273F68(p, pcm, o);
        if (r == -1) {
            if (!pcm->x2F4 && !p->x120) {
                int f = 0;
                if (func_0013B500(o, 0x33)) {
                    if (o->x33C != -1 && o->x33C != 0x12)
                        f = 1;
                    else if (!o->x10D4)
                        f = !o->x218;
                } else {
                    f = func_0013B500(o, 0x3A) && func_002387A8(o->a29C, 0xCB);
                }
                if (f)
                    continue;
            }
            r = func_00119C90(p->x104, 0x7FFFFFFF, func_001C9428(0, p, Xf(o)->pos)) != 0;
        }
        if (r)
            func_00166150(pcm, p);
        else
            func_00166228(pcm, p);
    }
}
