// Default tuning values for a camera-like bounds object: base defaults, then limits, speeds, direction vectors and
// four bound slots filled from one shared pair.
// SLY3_CFLAGS: -Os -G0
struct BoundsPair { float low, high; };
struct BoundsSelf {
    unsigned char prefix0[0x164];
    int word164;
    unsigned char gap168[0x310 - 0x168];
    float v310[3];
    unsigned char gap31C[0x320 - 0x31C];
    float f320, f324, f328, f32C, f330, f334, f338;
    unsigned char gap33C[0x390 - 0x33C];
    float f390;
    unsigned char gap394[0x398 - 0x394];
    float f398;
    unsigned char gap39C[0x3D8 - 0x39C];
    float f3D8, f3DC;
    unsigned char gap3E0[0x3EC - 0x3E0];
    int word3EC;
    unsigned char gap3F0[0x3F8 - 0x3F0];
    int word3F8;
    unsigned char gap3FC[0x428 - 0x3FC];
    int word428;
    float v42C[3];
    unsigned char gap438[0x440 - 0x438];
    float v440[3];
    unsigned char gap44C[0x450 - 0x44C];
    int word450;
    float f454;
};
extern struct BoundsPair D_003256E0;
void func_001F3B50(void *receiver);
void func_001F43F8(void *receiver, int value);
void func_00207568(void *state, int index, float value, struct BoundsPair *pair);
void func_00203C18(struct BoundsSelf *self)
{
    float *a, *b, *c;
    unsigned int i;
    func_001F3B50(self);
    self->f32C = 1100.0f;
    self->f330 = 700.0f;
    self->f338 = 1.5f;
    self->f334 = 0.8f;
    a = self->v310;
    a[0] = 2500.0f;
    a[1] = -1500.0f;
    a[2] = 0.0f;
    self->f320 = 0.0f;
    self->f390 = 100.0f;
    self->f328 = 3500.0f;
    self->f324 = 2500.0f;
    func_001F43F8(self, 100);
    self->f3D8 = 10.0f;
    self->f3DC = 3000.0f;
    self->f398 = 1.0f;
    self->word3EC = -1;
    self->word3F8 = -1;
    self->word428 = 1;
    b = self->v42C;
    b[0] = 4.0f;
    b[1] = 0.0f;
    b[2] = 0.5f;
    c = self->v440;
    c[0] = 1.0f;
    c[1] = 0.0f;
    c[2] = 0.0f;
    self->f454 = 1.0f;
    self->word164 = 0x20;
    self->word450 = 0;
    for (i = 0; i < 4; i++)
        func_00207568(self, i, 50.0f, &D_003256E0);
}
