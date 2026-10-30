// SLY3_CFLAGS: -Os -G0
typedef int ti128 __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct E { char pad[0x1c]; int f1c; };
struct O { int pad[3]; struct VTE *vt; char pad2[0xd4 - 0x10]; struct E *pe; };
struct Q { char pad[0x40]; ti128 v40; int f50; };
struct S { char pad[0x1108]; void *f1108; char pad2[0x1900 - 0x110c]; int f1900; void *f1904; void *f1908; struct Q *pq; ti128 v1910; float f1920; };
extern ti128 D_00317560;
extern float D_0036BB98;
int func_00173428(void *);
struct O *func_001FBE30(void *, int);
void func_0013EB08(struct S *, struct O *);
void func_00212770(struct Q *, struct O *);
void func_0014CB98(struct O *, float);
void func_0013F970(struct S *, int);
static inline int Busy(struct S *p) { int r = 0; if (p->f1108) r = func_00173428(p->f1108) != 0; return r; }
void func_0013EB68(struct S *p, int a) {
    void *pv;
    struct O *po;
    struct Q *pq;
    if (Busy(p)) return;
    switch (p->f1900) {
    case 0: pv = p->f1904; break;
    case 1: pv = p->f1908; break;
    default: return;
    }
    if (!pv) return;
    po = func_001FBE30(pv, 0);
    if (!po) return;
    func_0013EB08(p, po);
    po->pe->f1c = a;
    pq = p->pq;
    pq->f50 = 0;
    pq->v40 = p->v1910;
    func_00212770(pq, po);
    ((void (*)(void *, ti128))po->vt[41].pfn)((char *)po + po->vt[41].d, D_00317560);
    func_0014CB98(po, 4.0f);
    func_0013F970(p, 1);
    p->f1920 = D_0036BB98;
}
