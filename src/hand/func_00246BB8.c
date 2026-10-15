// Initialize the actual resource singleton and its arrays/three-float transition records.
// Receiver is explicitly forwarded to the actual pointer-returning base constructor.
// Helper11EDF8 consumes destinationA0 and F12-F15; writes12 bytes, preserving each adjacent fourth word.
// P is only the accessed prefix; no total dynamic object size or semantic class name is asserted.
// SLY3_CFLAGS: -Os -G0
// Explicit real base receiver; helper11EDF8 consumes destinationA0/F12-F15.
struct T {
    float a;
    float b;
    float c;
};
struct V2 {
    float x, y;
};
struct P {
    int n0;
    int n4;
    int pad8;
    void *pvt;
    int n10;
    char pad14[0x1C - 0x14];
    char x1C[0x18];
    char x34[0x18];
    char x4C[0xC];
    int n58;
    char pad5C[0x68 - 0x5C];
    int n68;
    char pad6C[0x80 - 0x6C];
    char x80[0x10];
    char x90[0x10];
    char padA0[0x104 - 0xA0];
    int n104;
    char pad108[0x118 - 0x108];
    struct T t118;
    struct T t124;
    struct T t130;
    char pad13C[0x210 - 0x13C];
    int n210;
    int pad214;
    int a218[8];
    int n238;
};
extern char D_00350A20[];
extern const struct V2 D_00326FE0;
extern const struct V2 D_00326FE8;
struct P *func_002B8670(struct P *);
void *func_0011E100(void *, int, int, int);
void func_0011AF38(void *, int);
void func_0011EDF8(float, float, float, void *, float);
static inline void InitT(struct T *pt, float a, float c) {
    pt->a = a;
    pt->b = 0.0f;
    pt->c = c;
}
struct P *func_00246BB8(struct P *p) {
    int n;
    int *q;
    func_002B8670(p);
    p->pvt = D_00350A20;
    func_0011E100(p->x1C, 0x70, 0x80, 0x10);
    func_0011E100(p->x34, 0x3C0, 0x10, 0x10);
    p->n210 = 0;
    q = p->a218;
    for (n = 7; n != -1; n--) *q++ = 0;
    p->n238 = 0;
    func_0011AF38(p->x4C, 0x3C);
    p->n68 = 3;
    p->n10 = 0;
    p->n104 = 0;
    InitT(&p->t130, 1.0f, 0.25f);
    InitT(&p->t124, 1.0f, 0.25f);
    {
        struct T *pt = &p->t118;
        float b;
        float h = 0.5f;
        InitT(pt, 3.0f, 0.25f);
        b = pt->b;
        func_0011EDF8(b, D_00326FE0.y, h, p->x80, D_00326FE0.x);
        func_0011EDF8(b, D_00326FE8.y, h, p->x90, D_00326FE8.x);
    }
    p->n58 = 0;
    return p;
}
