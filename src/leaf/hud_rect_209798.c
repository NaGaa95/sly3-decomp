// SLY3_CFLAGS: -O2 -G0 -ffast-math
// Fills a HUD rectangle given by two corners in 640x480 space with the (half-alpha) colour; the GS register values are 64-bit (unsigned long) arguments.
union Color { unsigned int rgba; struct { unsigned char r, g, b, a; } c; };
struct Screen { int pad0; int width; int height; };
extern struct Screen D_0036DBE0;
void func_0018CA08(void *ctx, int a, int b, unsigned long c);
void func_0018CCC0(void *ctx, int a, unsigned long b);
void func_0018CAA0(void *ctx, unsigned int rgba);
void func_0018CC38(void *ctx, int a, int b, int c, int d);
float func_002BE228(void *g, float v);
float func_002BE248(void *g, float v);
float func_002BE2E8(void *g, float v);
float func_002BE230(void *g, float v);
float func_002BE298(void *g, float v);
float func_002BE2F8(void *g, float v);
void func_00209798(union Color *color, void *ctx, float x1, float y1, float x2, float y2)
{
    int px, py, qx, qy;
    unsigned int limit = 0xFE;
    func_0018CA08(ctx, color->c.a <= limit ? 0x46 : 6, 5, 0x441EE);
    color->c.a = (color->c.a + 1) >> 1;
    func_0018CCC0(ctx, 0x47, 0x31001);
    func_0018CCC0(ctx, 0x42, 0x44);
    func_0018CAA0(ctx, color->rgba);
    x1 *= D_0036DBE0.width;
    px = (int)func_002BE2E8(&D_0036DBE0, func_002BE248(&D_0036DBE0, func_002BE228(&D_0036DBE0, x1 * 0.0015625f)));
    y1 *= D_0036DBE0.height;
    py = (int)func_002BE2F8(&D_0036DBE0, func_002BE298(&D_0036DBE0, func_002BE230(&D_0036DBE0, y1 * 0.0020833334f)));
    func_0018CC38(ctx, px, py, 0, 0);
    x2 *= D_0036DBE0.width;
    qx = (int)func_002BE2E8(&D_0036DBE0, func_002BE248(&D_0036DBE0, func_002BE228(&D_0036DBE0, x2 * 0.0015625f)));
    y2 *= D_0036DBE0.height;
    qy = (int)func_002BE2F8(&D_0036DBE0, func_002BE298(&D_0036DBE0, func_002BE230(&D_0036DBE0, y2 * 0.0020833334f)));
    func_0018CC38(ctx, qx, qy, 0, 0);
}
