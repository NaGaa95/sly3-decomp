// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sly 2 func_001C9688 is the reference; Sly 3 adds a second RGBA field to each record.
struct RGBA { unsigned char r, g, b, a; };
struct COLOR_ENTRY { int n; void *p; struct RGBA c, c2; };
extern "C" struct COLOR_ENTRY D_00467B90[5];
extern "C" char D_00347770[], D_003479F0[], D_00347AF8[], D_00347B80[], D_00347C08[];
extern "C" void *func_00292034(void *p, int c, int cb);
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
static inline void SetRgba(struct RGBA *pc, int r, int g, int b, int a) { pc->r = r; pc->g = g; pc->b = b; pc->a = a; }
extern "C" void func_001FA280(int init, int prio)
{
    if (prio == 0xFFFF && init) {
        struct COLOR_ENTRY *pe = D_00467B90;
        func_00292034(pe, 0, sizeof(struct COLOR_ENTRY));
        pe->n = 0x35;
        pe->p = D_00347770;
        SetRgba(&pe->c, 0x2F, 0x3A, 0x7F, 0x7F);
        SetRgba(&pe->c2, 0x2f, 0x2f, 0x2f, 0x7F);
        pe++;
        func_00292034(pe, 0, sizeof(struct COLOR_ENTRY));
        pe->n = 0x16;
        pe->p = D_003479F0;
        SetRgba(&pe->c, 0x2F, 0x3A, 0x7F, 0x7F);
        SetRgba(&pe->c2, 0x2f, 0x2f, 0x2f, 0x7F);
        pe++;
        func_00292034(pe, 0, sizeof(struct COLOR_ENTRY));
        pe->n = 0xB;
        pe->p = D_00347AF8;
        SetRgba(&pe->c, 0x5F, 0x5F, 0x5F, 0x7F);
        SetRgba(&pe->c2, 0x7f, 0x3f, 0x3f, 0x7F);
        pe++;
        func_00292034(pe, 0, sizeof(struct COLOR_ENTRY));
        pe->n = 0xB;
        pe->p = D_00347B80;
        SetRgba(&pe->c, 0x5F, 0x5F, 0x5F, 0x7F);
        SetRgba(&pe->c2, 0x3f, 0x7f, 0x7f, 0x7F);
        pe++;
        func_00292034(pe, 0, sizeof(struct COLOR_ENTRY));
        pe->n = 0x3E;
        pe->p = D_00347C08;
        SetRgba(&pe->c, 0x5F, 0x5F, 0x5F, 0x7F);
        SetRgba(&pe->c2, 0x3f, 0x3f, 0x3f, 0x7F);
            if (++D_0036AE78 == 1)
                func_0011E100(D_004D2AD8, 16, 2048, 16);
            if (++D_0036AE7C == 1)
                func_0011E100(D_004D2BB0, 24, 1024, 16);
            if (++D_0036AE80 == 1)
                func_0011E100(D_004D2C88, 24, 256, 16);
            if (++D_0036AE84 == 1)
                func_0011E100(D_004D2D60, 28, 1024, 16);
            if (++D_0036AE88 == 1)
                func_0011E100(D_004D2E38, 12, 256, 16);
            if (++D_0036AE8C == 1)
                func_0011E100(D_004D2F10, 24, 256, 16);
    }
}
