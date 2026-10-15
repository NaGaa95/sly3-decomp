// Reference algorithm: src/hand/func_001F26A8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct L { char pad[0x24]; struct L *next; char pad2[0x54 - 0x28]; struct L *first; char pad3[0x60 - 0x58]; struct L *end; };
void func_0023B3A8(struct L *);
int func_0013B500(struct L *, int);
void func_0023B550(struct L *p)
{
    struct L *q;
    func_0023B3A8(p);
    for (q = p->first; q != p->end; q = q->next) {
        if (func_0013B500(q, 0x2F)) func_0023B550(q);
    }
}
