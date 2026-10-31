// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
void func_00238970(void *p);
struct S { char pad[0x60]; int n60; int pad64; float g68; float g6C; float g70; int n74; float g78; float g7C; float g80; float g84; };
void func_00157AA0(struct S *p)
{
    func_00238970(p);
    p->n60 = -1;
    p->g68 = 0.25f;
    p->g78 = 250.0f;
    p->g7C = 350.0f;
    p->g80 = 1.0f;
    p->g84 = 1.2f;
    p->g6C = 3.402823466e+38f;
    p->g70 = 3.402823466e+38f;
    p->n74 = 1;
}
