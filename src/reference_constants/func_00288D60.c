// Reference algorithm: src/hand/func_0022B198.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { int k; char pad[0x4C]; void *o; };
int func_00260758(void *o, int a);
void func_00288C58(struct S *p, int k);
void func_00288D60(struct S *p)
{
    int k = p->k;
    switch (k) {
    case 0: break;
    case 1: if (!func_00260758(p->o, 0x37B)) k = 3; break;
    case 2: if (!func_00260758(p->o, 0x37B)) k = 0; break;
    }
    func_00288C58(p, k);
}
