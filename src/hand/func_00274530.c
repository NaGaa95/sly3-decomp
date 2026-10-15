// Select or create a 144-byte entry in the four-entry state collection, copying the preceding entry or default descriptor.
// Reference algorithm: src/hand/func_00221818.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct E { int id; int pad[3]; qword q[8]; };
extern struct E D_00349FB0;
struct S { char pad[0x10C]; int c; struct E *a; struct E *cur; int x11C; };
void func_00274660(struct S *p, int id);
void func_00274530(struct S *p, int id)
{
    int i;
    struct E *entry;
    struct E *pe;
    func_00274660(p, id);
    if (p->c >= 4) return;
    for (i = 0; i < p->c; i++) {
        if ((entry = p->a + i)->id == id) {
            p->cur = entry;
            return;
        }
    }
    if (p->x11C) {
        p->cur = p->a;
        return;
    }
    pe = &p->a[p->c++];
    p->cur = pe;
    if (p->c >= 2)
        *pe = p->a[p->c - 2];
    else
        *pe = D_00349FB0;
    p->cur->id = id;
}
