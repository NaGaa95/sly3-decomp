// Initialize the base state and identifier fields, update its mode, and set flag 2 in immediate or indirect flag storage.
// Reference algorithm: src/hand/func_002281E8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; int f; char pad2[0x138]; int a, b; };
static inline int FIsPtr(int f) { return !(f & 1); }
void func_0028FD70(struct S *p);
void func_001C9118(struct S *p, int a);
void func_0027FAC8(struct S *p)
{
    int f;
    func_0028FD70(p);
    p->a = 0x1A8;
    p->b = -1;
    func_001C9118(p, 0);
    f = p->f;
    if (FIsPtr(f)) *(int *)f |= 2;
    else p->f = f | 2;
}
