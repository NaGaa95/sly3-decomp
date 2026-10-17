// SLY3_CFLAGS: -Os -G0
struct InitColor { unsigned char r, g, b, a; };
struct V3 { float x, y, z; };
struct InitSelf {
    unsigned char prefix[0x10]; int word10; float f14; float f18; float f1c; struct InitColor color;
    unsigned char gap24[0x34 - 0x24]; int word34; float f38; float f3c; float f40;
    unsigned char gap44[0x50 - 0x44]; struct V3 v50; float f5c; struct V3 v60; float f6c; float f70; int word74;
    unsigned char gap78[0x88 - 0x78]; float f88; float f8c; float f90; float f94; float f98;
    unsigned char gap9C[4]; unsigned char colors[0x10]; unsigned char gapB0[0xD0 - 0xB0]; unsigned char tail[8]; int wordD8; int wordDC;
};
extern int D_0036BC00;
extern int D_0036BC04;
void func_00169398(void *self);
void *func_00292034(void *destination, int byte, unsigned int bytes);

static inline void SetV3(struct V3 *v, float x, float y, float z) { v->x = x; v->y = y; v->z = z; }
static inline void SetV3b(struct V3 *v, float x, float y, float z) { v->z = z; v->y = y; v->x = x; }
void func_00168FE0(struct InitSelf *self)
{
    self->word10 = -1;
    self->wordDC = 0;
    if(!D_0036BC04) {
        D_0036BC00 = 0x80303030;
        D_0036BC04 = 1;
    }
    self->f14 = 500.0f;
    self->f18 = 20000.0f;
    self->f1c = 0.5f;
    self->color = *(struct InitColor *)&D_0036BC00;
    self->word34 = 0x80000000;
    self->f38 = 1.5f;
    self->f3c = 1.2f;
    self->f40 = 1.4f;
    SetV3b(&self->v50, 0.0f, 0.0f, 0.0f);
    SetV3(&self->v60, 180.0f, 255.0f, 255.0f);
    self->f70 = 90.0f;
    self->word74 = 0;
    func_00169398(self);
    self->f90 = 128.0f;
    self->f94 = 96.0f;
    self->f98 = 160.0f;
    func_00292034(self->colors, 0, 0x10);
    func_00292034(self->tail, 0, 8);
    self->f88 = 165.0f;
    self->f8c = 0.5f;
    self->wordD8 = 0;
}
