// Reference algorithm: src/hand/func_001ACC38.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct H { char pad[0x13950]; int x; };
extern struct H D_00375290;
struct CLOCK { float t; float dt; char pad[0x34]; float t3c; };
extern struct CLOCK D_0036BB9C;
struct S { char pad[0x58]; int x44; float x48; };
void func_001D0D30(struct S *p, int n)
{
    if (n == p->x44) return;
    switch (n) { case 2: case 3: D_00375290.x = 0; }
    p->x44 = n;
    p->x48 = D_0036BB9C.t3c;
}
