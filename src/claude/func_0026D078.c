// SLY3_CFLAGS: -Os -G0
// Start the state's animation once: pick the clip by mode (+0x198) and stance (+0x278), place the target
// actor relative to the camera, then apply the clip.
typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x40]; qword v40; int n50; };
struct S
{
    char pad0[0x198];
    int mode;
    char pad19C[0x234 - 0x19C];
    void *apo[3];
    struct T *pt;
    char pad244[0x250 - 0x244];
    qword v250;
    char pad260[0x278 - 0x260];
    int stance;
    char pad27C[0x298 - 0x27C];
    void *paseg298, *paseg29C, *paseg2A0;
    char pad2A4[0x2B8 - 0x2A4];
    void *pasega;
};
extern qword D_00317560;
void *func_001FBE30(void *po, int n);
void *func_001F4A80(struct S *p);
qword func_00212FA0(void *po, void *pcam, qword a, qword b, int n);
qword func_001C9428(int n, struct T *pt, qword v);
void func_00212770(struct T *pt, void *po);
int func_0013B500(void *po, int cid);
void func_0014D1F0(void *po, struct S *p);
void func_00137588(void *paseg, void *palo, float t, float svt, int grf, void **ppasega);
void func_0026D078(struct S *p)
{
    void *paseg;
    void *po;
    if (p->pasega)
        return;
    paseg = 0;
    po = 0;
    switch (p->mode) {
    case 1:
    case 2:
        paseg = p->paseg29C;
        break;
    case 0:
        paseg = p->paseg298;
        break;
    }
    switch (p->stance) {
    case 1:
        paseg = p->paseg2A0;
    case 0:
        po = func_001FBE30(p->apo[0], 0);
        break;
    case 3:
        if (p->apo[1])
            po = func_001FBE30(p->apo[1], 0);
        break;
    case 4:
        if (p->apo[2])
            po = func_001FBE30(p->apo[2], 0);
        break;
    }
    if (po) {
        qword v = func_00212FA0(po, func_001F4A80(p), D_00317560, p->v250, 0);
        struct T *pt;
        p->pt->n50 = 0;
        pt = p->pt;
        pt->v40 = func_001C9428(0, pt, v);
        func_00212770(p->pt, po);
        if (func_0013B500(po, 0x59))
            func_0014D1F0(po, p);
    }
    if (paseg)
        func_00137588(paseg, p, 0.0f, 1.0f, 0, &p->pasega);
}
