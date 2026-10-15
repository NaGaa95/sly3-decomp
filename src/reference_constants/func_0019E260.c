// Reference algorithm: src/hand/func_001817E8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x3C]; int fl; char p2[0x278]; char dl[0xC]; };
void func_0019B420(struct S *p);
void func_0011AF38(void *pdl, int ib);
void func_0019E260(struct S *p)
{
    int v;
    func_0019B420(p);
    v = p->fl;
    if ((v ^ 1) & 1) *(int *)v |= 8;
    else p->fl = v | 8;
    func_0011AF38(p->dl, 0x60);
}
