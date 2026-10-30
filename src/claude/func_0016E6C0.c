// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { struct { qword r[4]; } q; float af[4][4]; } M4;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
struct B { unsigned char ab[16]; };
static const int s_aid[4] = { 8, 9, 10, 11 };
struct LO;
struct VTE { short d; short pad; void *pfn; };
struct LO { int a[3]; char *pvt; };
#define PVTE(plo, off) ((struct VTE *)((plo)->pvt + (off)))
struct PO { struct LO lo; char pad[0x3C - 0x10]; int x3C; char pad1[0xCC - 0x40]; int xCC; };
struct ALO { struct LO lo; char pad[0x1BC - 0x10]; float g1BC; char pad1[0x29C - 0x1C0]; char x29C[0x2F4 - 0x29C]; struct B b2F4; };
struct T { char pad[0x58]; float g58; };
struct PV { int k; struct T *pt; };
struct S { char pad[0x10]; struct ALO *palo; char pad1[0x18 - 0x14]; char x18[0x30 - 0x18]; int k30; float t34; };
void func_00238AE8(void *p);
void func_00238AB8(struct S *p);
void func_00252AD0(struct B *pb, int id);
struct PV *func_00255130(struct ALO *palo, struct B b);
struct PO *func_00238690(void *p, int n);
float func_0011E3B8(float g);
qword func_0011FD70(float a, float b, float c);
void func_00132930(struct PO *po, qword pos);
static inline M4 *VMat(struct LO *plo) { struct VTE *e = PVTE(plo, 0x120); return ((M4 *(*)(struct LO *))e->pfn)((struct LO *)((char *)plo + e->d)); }
static inline void VPost(struct PO *po) { struct VTE *e = PVTE(&po->lo, 0x40); ((void (*)(struct LO *))e->pfn)((struct LO *)((char *)po + e->d)); }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline struct B BitsOr(const struct B *pa, const struct B *pb)
{
    struct B r;
    int i;
    for (i = 0; i < 16; i++)
        r.ab[i] = pa->ab[i] | pb->ab[i];
    return r;
}
void func_0016E6C0(struct S *p, int k)
{
    if (p->k30 == k)
        return;
    func_00238AE8(p->x18);
    p->k30 = k;
    p->t34 = D_0036BB98.t;
    switch (k) {
    case 0:
    case 1:
    case 2:
    case 3: {
        int id = s_aid[k];
        struct B b, b0;
        struct PV *pv;
        func_00252AD0(&b0, id);
        b = BitsOr(&p->palo->b2F4, &b0);
        pv = func_00255130(p->palo, b);
        if (pv) {
            switch (pv->k) {
            case 2: {
                struct PO *po = func_00238690(p->palo->x29C, 0xCB);
                qword q;
                po->x3C = id;
                po->xCC = 7;
                q = func_0011FD70(func_0011E3B8(p->palo->g1BC + 3.14159265f), pv->pt->g58, 0.0f);
                func_00132930(po, Add(VMat(&p->palo->lo)->q.r[3], q));
                VPost(po);
                return;
            }
            case 0: {
                struct PO *po = func_00238690(p->palo->x29C, 0xC9);
                po->x3C = id;
                VPost(po);
                return;
            }
            }
        }
        p->k30 = -1;
        func_00238AB8(p);
        break;
    }
    case -1:
        func_00238AB8(p);
        break;
    }
}
