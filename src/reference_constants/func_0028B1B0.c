// Reference algorithm: src/hand/func_0022C840.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pf)(); };
struct O { int a[3]; struct VTE *vt; };
struct Q { char pad[0x80]; float a, b; void *pa, *pb; char pad2[8]; short k; short l; };
extern float D_00329830;
extern char D_0034A150[];
void func_0028B1B0(struct O *p, struct Q *q)
{
    switch (q->k) {
    case 0: case 1: case 2: case 3: case 14: case 15: case 16: case 17: case 21: case 22:
        break;
    default:
        q->b = D_00329830;
        q->a = D_00329830;
        q->pb = D_0034A150;
        q->pa = D_0034A150;
        break;
    }
    q->l = 0;
    p->vt[51].pf((char *)p + p->vt[51].d, 4);
}
