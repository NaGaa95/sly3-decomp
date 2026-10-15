// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct VE {
    short d;
    short pad;
    void (*pf)(void *);
};
struct O {
    char pad0[0xC];
    struct VE *vt;
    char pad1[0x28 - 0x10];
    unsigned long fl28;
    char pad2[0x10D0 - 0x30];
    void *object10D0;
    char pad3[0x1158 - 0x10D4];
    float timestamp1158;
    int pad4;
    int kind1160;
};
struct S {
    char pad[0x40];
    int c;
    struct O **apo;
};
struct L {
    int k;
    unsigned char opaque4[12];
};
extern struct {
    float t;
    float dt;
}
D_0036BB98;
extern const float D_00327498;
void func_001C8168(struct S *p);
void *func_002387A8(void *list, int n);
void *func_00292034(void *p, int c, int n);
void func_0019A2D0(void *p, struct L *pl);
void func_00170360(void *p);
void func_00257348(struct S *p) {
    int i, c;
    struct O **apo;
    func_001C8168(p);
    c = p->c;
    apo = p->apo;
    for (i = 0; i < c; i++) {
        struct O *o = apo[i];
        if (((int)(o->fl28 >> 56) & 1) && D_0036BB98.t - o->timestamp1158 > 0.25f) {
            switch (o->kind1160) {
                case 0: break;
                case 1: o->vt[9].pf((char *)o + o->vt[9].d);
                break;
                case 2: {
                    void *x = func_002387A8((char *)o + 0x29C, 0xC8);
                    if (x) {
                        struct L l;
                        func_00292034(&l, 0, sizeof(l));
                        l.k = 1;
                        func_0019A2D0(x, &l);
                    }
                    func_00170360(o->object10D0);
                    break;
                }
            }
            o->timestamp1158 = D_00327498;
        }
    }
}
