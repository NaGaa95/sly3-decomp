// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-entry reference sampling for two tracked entries: query two positions of the path object and store the height ratio
// (v0.z - v1.z) / radius, then run the shared multi-entry resolve (same routine as Sly 2 func_0019DE58).
struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
typedef struct { short d; short pad; void (*pfn)(void *, float, float, struct VECTOR *, int); } VT;
struct C { VT *vt; };
struct R { int x0; struct C *x4; };
struct O { char pad[0x64]; float x64; };
struct E { int x0; struct O *x4; int x8; float xc; };
struct P { int x0; char pad[0x50 - 4]; struct E ae[2]; int x70; };
extern "C" {
struct R *func_00136EE0(struct O *o, int a, int b, int c);
void func_00147E08(int a, int b, int c, void *d, int e, int f, int g, void *h);
}
extern "C" void func_001BEE70(struct P *p)
{
    int i;
    struct VECTOR v0, v1;
    for (i = 0; i < 2; i++) {
        struct E *e = &p->ae[i];
        struct O *o = e->x4;
        if (o) {
            struct R *r = func_00136EE0(o, p->x0, 1, 1);
            if (r) {
                r->x4->vt[3].pfn((char *)r->x4 + r->x4->vt[3].d, 0.0f, 1.0f, &v0, 0);
                r->x4->vt[3].pfn((char *)r->x4 + r->x4->vt[3].d, o->x64, 1.0f, &v1, 0);
                e->xc = (v0.z - v1.z) / o->x64;
            }
        }
    }
    func_00147E08(p->x0, 0x10, 2, p->ae, 0, 0, 0, &p->x70);
}
