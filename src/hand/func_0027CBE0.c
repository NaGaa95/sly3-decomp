// Initialize paired scalar limits and copy the reference two-component value, then set the current scalar, status flags, and self pointer.
// Reference algorithm: src/hand/func_002259D8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V2 { float x, y; };
struct S { char pad[0x1AC]; float a, b, c, d; struct V2 e; float pad2[2]; float f; int pad3[3]; int g; void *h; int i; };
extern struct V2 D_00329460;
void func_001F3B50(struct S *p);
void func_0027CBE0(struct S *p)
{
    func_001F3B50(p);
    p->e = D_00329460;
    p->g = 1; /*P*/
    p->f = p->e.y; /*P*/
    p->c = -1.5f; /*P*/
    p->d = 1.5f; /*P*/
    p->a = -0.7f; /*P*/
    p->b = 0.7f; /*P*/
    p->i = 1; /*P*/
    p->h = p; /*P*/
}
