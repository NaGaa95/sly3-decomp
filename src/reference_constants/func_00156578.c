// Reference algorithm: src/hand/func_00143EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct P { char pad[0xC]; struct VTE *vt; char pad2[0x113C - 0x10]; char m1030[4]; char m1034[4]; };
extern char D_00475480[];
void func_00156690(struct P *p);
void *func_0017E1B8(void *g, int k, int oid, struct P *p);
int func_0013B500(void *o, int n);
void func_0023AC58(void *p);
void func_00137588(void *o, struct P *p, int a, void *b, float f, float g);
void func_00137628(void *p);
void func_0023AAE8(void *o, struct P *p, int n, int a, void *b);
void func_00156578(struct P *p, int oid, int a, int b)
{
    void *o;
    if (oid == -1) {
        func_00156690(p);
        return;
    }
    o = func_0017E1B8(D_00475480, 1, oid, p);
    if (!o) return;
    if (func_0013B500(o, 0x82)) {
        p->vt[99].pfn((char *)p + p->vt[99].d, b);
        func_0023AC58(p->m1034);
        func_00137588(o, p, a, p->m1030, 0.0f, 1.0f);
    } else if (func_0013B500(o, 0x84)) {
        p->vt[99].pfn((char *)p + p->vt[99].d, b);
        func_00137628(p->m1030);
        func_0023AAE8(o, p, -1, a, p->m1034);
    }
}
