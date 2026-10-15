// Reference algorithm: src/hand/func_001C2078.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0x28]; int n; };
struct G { char pad[0x4510]; int c; char pad2[0x8E8]; struct O *po; };
extern struct G D_00475480;
void func_001C7938(void *p);
void func_001EE968(void *p)
{
    struct G *pg;
    int c;
    func_001C7938(p);
    pg = &D_00475480;
    c = pg->c + 1;
    pg->c = c;
    pg->po->n = c;
}
