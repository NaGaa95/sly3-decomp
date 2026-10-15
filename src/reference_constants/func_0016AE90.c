// Reference algorithm: src/hand/func_00150EF0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct S {
    int pad[10]; float g18; int pad1c;
    qword q20; qword q30; qword q40; qword q50; qword q60; float g70; int pad74[3];
    qword q80; qword q90; float gA0; int padA4[2]; float gAC;
};
qword func_0016A750(struct S *p);
qword func_0016A7E8(struct S *p);
void func_0016AE90(struct S *p)
{
    p->q20 = func_0016A750(p);
    p->q30 = func_0016A7E8(p);
    if (0.0f <= p->g18)
        p->gAC = p->g18;
    p->q50 = p->q80;
    p->q60 = p->q90;
    p->g70 = p->gA0;
}
