// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct V3 { float a, b, c; };
struct Self {
    unsigned char pad0[0x1B0];
    int f1B0;
    unsigned char pad1B4[0x2C];
    float f1E0, f1E4, f1E8, f1EC, f1F0, f1F4, f1F8, f1FC, f200, f204, f208, f20C, f210;
    int f214;
    unsigned char pad218[0x8];
    float f220;
    unsigned char pad224[0x1A8];
    float f3CC, f3D0;
    unsigned char pad3D4[0xC];
    struct V3 f3E0;
    unsigned char pad3EC[4];
    float f3F0, f3F4, f3F8, f3FC, f400, f404;
    int f408;
    float f40C;
    unsigned char pad410[0x18];
    float f428, f42C;
    unsigned char pad430[0xD0];
    float f500, f504, f508, f50C, f510, f514;
    unsigned char pad518[0x34];
    int f54C;
    unsigned char pad550[0xC];
    int f55C;
};
void func_001F3B50(void *self);
void func_00213988(void);
void func_00219490(struct Self *self);
static inline void Set3(struct V3 *p, float a, float b, float c) { p->a = a; p->b = b; p->c = c; }
void func_002139D0(struct Self *self)
{
    func_001F3B50(self);
    func_00213988();
    {
    float kTilt = 0.26179942f;
    self->f3F8 = -kTilt;
    self->f1B0 = -1;
    self->f40C = 0.5f;
    self->f3FC = kTilt;
    self->f428 = 20000.0f;
    self->f42C = 7500.0f;
    self->f408 = 4;
    self->f3CC = 0.1f;
    self->f3D0 = 30000.0f;
    Set3(&self->f3E0, 0.35f, 0.00005f, 0.0f);
    self->f3F0 = 0.03490659f;
    self->f3F4 = 0.13962635f;
    self->f400 = 10.0f;
    self->f404 = 20.0f;
    self->f500 = 6.0f;
    self->f504 = 12.0f;
    self->f1E0 = 0.3f;
    self->f1E4 = 0.5f;
    self->f1E8 = 0.743f;
    self->f1EC = 0.9f;
    self->f1F0 = 1.1f;
    self->f20C = 1.3f;
    self->f1F4 = 1.2f;
    self->f1F8 = 1.55f;
    self->f1FC = 1.5f;
    self->f200 = 1.45f;
    self->f204 = 1.4f;
    self->f208 = 1.35f;
    self->f210 = 1.3f;
    self->f214 = 13;
    self->f220 = 4000.0f;
    self->f508 = 100.0f;
    self->f50C = 200.0f;
    self->f510 = 200.0f;
    self->f514 = 400.0f;
    self->f54C = -1;
    self->f55C = -1;
    }
    func_00219490(self);
}
