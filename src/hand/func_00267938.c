// Return whether the resource has a positive signed count and no backing pointer.
// Reference algorithm: src/hand/func_00218710.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct B { char pad[8]; short h; char pad2[6]; int p; };
struct S { char pad[8]; struct B *pb; };
int func_00267938(struct S *p)
{
    struct B *b = p->pb;
    if (b->h > 0 && b->p == 0)
        return 1;
    return 0;
}
