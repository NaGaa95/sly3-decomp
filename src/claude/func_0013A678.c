// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* attach a target: reset, remember it with full weight, pick an aim point (owner's override, else a query along the
   target's segment), optionally start effect 0x12 and refresh */
typedef int qword __attribute__((mode(TI)));
struct A { char pad[0x68]; void *p68; char pad2[0x7C - 0x6C]; int x7C; char pad3[0xC8 - 0x80]; float gC8; int padCC; qword vD0; qword vE0; };
struct O { char pad[0x320]; char a320[0x110C - 0x320]; float g110C; char pad2[0x11B4 - 0x1110]; int x11B4; };
struct T { struct O *po; int x4; int x8; struct A *pa; int x10; float g14; };
extern char D_0036C700[];
void func_001854C8(void *pv, int n, struct A *pa);
void func_0013ABC8(struct T *p, int n);
void func_001B0898(struct O *po, float g0, void *pv, qword a, qword b, float g1, float g2, int *pn, float *pg);
void func_001B7268(void *pv, int n, int a, int b, float g);
void func_0013A5B8(struct T *p);
void func_0013A678(struct T *p, struct A *pa, int f)
{
    func_001854C8(D_0036C700, 0x59, pa);
    func_0013ABC8(p, -1);
    p->pa = pa;
    p->g14 = 1.0f;
    if (!f) {
        struct O *po = p->po;
        if (po->x11B4) {
            p->x10 = po->x11B4;
        } else if (pa->p68) {
            int n;
            float g;
            func_001B0898(po, po->g110C, pa->p68, pa->vD0, pa->vE0, pa->gC8, 1.5f, &n, &g);
            if (n) {
                p->x10 = n;
                p->g14 = g;
            }
        }
    }
    if (p->pa->x7C)
        func_001B7268(p->po->a320, 0x12, 0, 0, 1.0f);
    func_0013A5B8(p);
}
