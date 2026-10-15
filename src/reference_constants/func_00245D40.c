// Reference algorithm: src/hand/func_001FBE80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct A { char pad[0x44]; int h; char pad2[12]; float g; };
void func_00291218(int h, int a, int b, int c);
void func_00291000(int h);
void func_00245D40(struct A *p)
{
    if (p->g > 0.0f)
        func_00291218(p->h, -4, (int)(p->g * 240.0f), 2);
    else
        func_00291000(p->h);
}
