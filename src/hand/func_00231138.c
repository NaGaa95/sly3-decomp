// Create the object with an identity matrix, allocate two scalar arrays and a quadword array, and initialize the first scalar array with its indices.
// Reference algorithm: src/hand/func_001E94B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct AR { int cb; int cbAlign; };
typedef struct { float m[4][4]; } MATRIX4;
struct X { char pad[0x50]; MATRIX4 mat; char pad2[0xE0 - 0xA0]; int xE0; int xE4; int xE8; float *ag; float *agF0; void *pvF4; };
struct X *func_00150690(int k, int n, void *pv, int m);
void func_00292034(void *p, int b, int cb);
void *func_001D2470(struct AR *par);
struct X *func_00231138(void *pv, int c)
{
    struct AR ar;
    int i;
    struct X *p = func_00150690(9, 0, pv, -1);
    MATRIX4 *pm;
    p->xE0 = 0;
    p->xE4 = 0;
    pm = &p->mat;
    func_00292034(pm, 0, 0x40);
    pm->m[3][3] = 1.0f; pm->m[2][2] = 1.0f; pm->m[1][1] = 1.0f; pm->m[0][0] = 1.0f;
    ar.cb = c * 4;
    ar.cbAlign = 0x10;
    p->ag = func_001D2470(&ar);
    for (i = 0; i < c; i++) p->ag[i] = i;
    ar.cb = c * 4;
    ar.cbAlign = 0x10;
    p->agF0 = func_001D2470(&ar);
    ar.cb = c * 16;
    ar.cbAlign = 0x10;
    p->pvF4 = func_001D2470(&ar);
    return p;
}
