// Reference algorithm: src/hand/func_0013B250.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int ti128 __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct Q { char pad[0x18]; int f18; };
struct S { int pad[3]; struct VTE *vt; char pad2[0x1CC - 0x10]; struct Q *f1e8; };
extern ti128 D_00317560;
#include "owner_parent_link.h"
void func_0023D938(struct S *, ti128);
void func_0023D9D0(struct S *, ti128);
void func_0023EBF8(struct S *, int);
void func_0023EC98(struct S *, int);
void func_0014C7F0(struct S *p, struct Q *q) {
    p->f1e8 = q;
    func_001C7A00(p, q->f18 != 1 ? q : 0, 3);
    func_0023D938(p, D_00317560);
    func_0023D9D0(p, D_00317560);
    func_0023EBF8(p, 1);
    func_0023EC98(p, 1);
    ((void (*)(void *, int, int, int, int, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 0x1E, 0, 0, 0, 0);
}
