// Reference algorithm: src/hand/func_001B1818.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword a[3]; } MATRIX3;
struct S { char pad[0x1B8]; float g; int pad2; MATRIX3 mat; };
extern qword D_00317550;
MATRIX3 func_0011C8C0(qword v, float g);
void func_001D6608(struct S *p, float g)
{
    p->g = g;
    p->mat = func_0011C8C0(D_00317550, g);
}
