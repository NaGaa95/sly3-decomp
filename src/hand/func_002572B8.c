// Count matching objects, allocate pointer storage for that count, and fill the resulting collection.
// Reference algorithm: src/hand/func_0020B500.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct G;
extern struct G D_00475480;
typedef struct ALLOCREQ { int cb; int nKind; } ALLOCREQ;
struct S { char pad[0x40]; int c; void **apv; };
void func_001C7DC8(struct S *p);
int func_0017E208(struct G *pg, int a, int b, int c, int cMax, void **apv);
void *func_001D2470(ALLOCREQ *preq);
void func_002572B8(struct S *p)
{
    ALLOCREQ req;
    func_001C7DC8(p);
    p->c = func_0017E208(&D_00475480, 0x605, 0x3A, 0, 0, 0);
    req.cb = p->c * 4;
    req.nKind = 0x10;
    p->apv = func_001D2470(&req);
    func_0017E208(&D_00475480, 0x405, 0x3A, 0, p->c, p->apv);
}
