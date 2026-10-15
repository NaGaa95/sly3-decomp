// Combine state predicates and virtual readiness with the matching object resource and mode tests.
// Reference algorithm: src/hand/func_00206380.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct { short d; short pad; void *pfn; } VTE;
struct Q { char pad[0xC]; VTE *vt; char pad2[0xDC - 0x10]; void *pEC; };
struct T { char pad[0xDC]; void *pEC; };
struct O { char pad[0x50]; int k; char pad2[8]; struct T *pt; };
struct S { char pad[0x29C]; char x26C[4]; };
int func_0023E178(struct S *p, struct Q *q);
int func_002533C0(struct S *p, int n);
struct O *func_002387A8(void *p, int n);
int func_0013CD00(int a, int b);
int func_00250D60(struct S *p, struct Q *q)
{
    int r = func_0023E178(p, q);
    if (func_002533C0(p, 7)) {
        if (!((int (*)(void *))q->vt[66].pfn)((char *)q + q->vt[66].d))
            r = func_0013CD00(r, 1);
    } else if (func_002533C0(p, 0x2A)) {
        struct O *o = func_002387A8(p->x26C, 0xDA);
        if (q->pEC == o->pt->pEC) {
            switch (o->k) {
            case 0:
            case 4:
            case 5:
                r = func_0013CD00(r, 1);
                break;
            }
        }
    }
    return r;
}
