// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE {
    short d;
    short pad;
    void (*pfn)(void *);
};
struct O {
    char pad[0xC];
    struct VTE *vt;
    char pad1[0x38 - 0x10];
    int x38;
    char pad2[0xB0 - 0x3C];
    struct X30 *xC0;
    int xC4;
    float gC8;
};
struct X30 {
    char pad[0x150];
    int x150;
};
struct P {
    char pad[0x10];
    void *p10;
    char pad1[4];
    char m18[0x30 - 0x18];
    struct X30 *p30;
    char pad2[0x60 - 0x34];
    int state;
    float tState;
    char pad3[0x90 - 0x68];
    qword v80;
    int x90;
};
struct CLOCK {
    float t;
};
extern struct CLOCK D_0036BB98;
void func_00238AE8(void *p);
struct O *func_00238690(void *p, int oid);
int func_0013B500(void *p, int n);
float func_0011E940(float a, float b);
void func_00158368(struct P *p);
void func_001C04E8(void *p, qword v);
int func_0013B868(void *p);
static __inline__ void Activate(struct P *p, int oid) {
    struct O *po = func_00238690((char *)p->p10 + 0x29C, oid);
    po->x38 = p->x90;
    po->vt[8].pfn((char *)po + po->vt[8].d);
}
void func_001586C0(struct P *p, int state) {
    if (state == p->state) return;
    func_00238AE8(p->m18);
    p->state = state;
    p->tState = D_0036BB98.t;
    switch (state) {
        case 0: {
            struct O *po = func_00238690((char *)p->p10 + 0x29C, 0xEF);
            if (func_0013B500(p->p30, 0x31)) {
                po->xC0 = p->p30;
                po->xC4 = 8;
                po->gC8 = func_0011E940(0.1f, 0.3f);
            }
            func_00158368(p);
            po->vt[8].pfn((char *)po + po->vt[8].d);
            break;
        }
        case 1: func_001C04E8(p->p10, p->v80);
        break;
        case 2: switch (func_0013B868(p->p10)) {
            case 0x35: Activate(p, 0xF6);
            break;
            case 0x36: Activate(p, 0xF7);
            break;
            case 0x34: Activate(p, 0xF8);
            break;
        }
        break;
    }
}
