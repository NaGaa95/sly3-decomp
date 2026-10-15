// Reference algorithm: src/hand/FUN_0015e1b0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct FONT { int pad[3]; int dy; int pad10; float ry; };
struct RT { int pad[5]; struct FONT *pfont; };
int func_00181910(struct RT *p, float dx);
float func_00181A90(struct RT *p, float dx)
{
    float dy = (float)p->pfont->dy * p->pfont->ry;
    return dy * (float)func_00181910(p, dx);
}
