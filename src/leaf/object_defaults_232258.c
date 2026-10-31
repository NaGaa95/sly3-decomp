// SLY3_CFLAGS: -Os -G0
// Object defaults on top of func_0023AE08: tuning floats, two counters, and flag bit 1 set on the (tagged) flag word at +0x3C.
struct Object {
    unsigned char pad00[0x3C]; int field3C;
    unsigned char pad40[0x16C - 0x40]; int i16C, i170, i174;
    unsigned char pad178[0x280 - 0x178];
    float f280; int i284; float f288, f28C; int i290; float f294, f298, f29C, f2A0;
    float f2A4, f2A8, f2AC, f2B0, f2B4, f2B8, f2BC;
};
void func_0023AE08(void *self);
void func_00240E58(void *self, int mask, int value);
void func_00232258(struct Object *self)
{
    int tagged;
    func_0023AE08(self);
    func_00240E58(self, 0x3FFFFFF, 2);
    self->i170 = 0x28;
    self->i174 = 0x28;
    self->i16C = -1;
    self->f280 = 0.5f;
    self->i284 = 0;
    self->f288 = 0.5f;
    self->f28C = 1200.0f;
    self->i290 = 0;
    self->f294 = 0.5f;
    self->f298 = 0.75f;
    self->f29C = 2000.0f;
    self->f2A0 = 1.0f;
    self->f2A4 = 10.0f;
    self->f2A8 = 3.0f;
    self->f2AC = 14.0f;
    self->f2B0 = 4.0f;
    self->f2B4 = 1.0f;
    self->f2B8 = 1.5f;
    self->f2BC = 1200.0f;
    tagged = self->field3C;
    if ((tagged ^ 1) & 1)
        *(int *)tagged |= 2;
    else
        self->field3C = tagged | 2;
}
