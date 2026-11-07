// SLY3_CFLAGS: -Os -G0
// Post-load: base init, find the bound object, init the sub-object, vtable slot 9, then (if a channel is set)
// resolve the two channels and sample the root transform at the marker time.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct M4 { qword r[4]; };
struct CHN { char pad[0xA0]; int nA0; };
struct MARKER { float t; };
struct S
{
    char pad0[0xC];
    struct VTE *vt;
    char pad10[0x6C - 0x10];
    int n6C, n70, n74;
    char pad78[0x80 - 0x78];
    qword v80;
    struct CHN *pchn90;
    void *p94;
    char pad98[0xA8 - 0x98];
    void *pA8;
    char padAC[4];
    char subB0[4];
    void *pB4;
};
extern char D_00475480[];
void func_001C7DC8(struct S *p);
void *func_0017E5D8(void *psw, int a, int b, struct S *p);
void func_00254C00(void *psub, void *po);
void *func_0023DDA0(void *po, int n, int m);
struct MARKER *func_00136880(void *paseg, int oid);
void func_00137070(void *paseg, void *po, void *pchn, int n, float t, float svt, struct M4 *pm, int f);

void func_00256AD0(struct S *p)
{
    func_001C7DC8(p);
    p->pA8 = func_0017E5D8(D_00475480, 3, 0x3A, p);
    func_00254C00(p->subB0, p->pA8);
    p->vt[9].pfn((char *)p + p->vt[9].delta);
    if (p->n6C != -1) {
        void *paseg;
        struct M4 m;
        p->pchn90 = func_0023DDA0(p->pA8, p->n6C, 6);
        p->p94 = func_0023DDA0(p->pA8, p->n70, 6);
        paseg = p->pB4;
        {
            struct MARKER *pm = func_00136880(paseg, p->n74);
            func_00137070(paseg, p->pA8, p->p94, p->pchn90->nA0, pm->t, 1.0f, &m, 0);
        }
        p->v80 = m.r[3];
    }
}
