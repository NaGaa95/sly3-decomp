// Reference algorithm: src/hand/func_001A23F8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern int D_00323740[];
struct Slot { void *value; char unknown[12]; };
struct S { int x0; int x4; char pad[0x30]; struct Slot a[1]; };
void *func_001C4088(struct S *p, int *pout)
{
    int i; void *r = 0; for (i = p->x4; i != -1 && (r = p->a[i].value) == 0; i = D_00323740[i]) ; *pout = 0; return r;
}
