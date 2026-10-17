// SLY3_CFLAGS: -Os -G0
struct CueRef { void *object; };
struct CueSelf {
    void *pose; unsigned char gap4[0x20 - 4];
    int clear20; int clear24; float rate; unsigned char gap2C[0x50 - 0x2C]; int clear50;
    unsigned char gap54[0xD0 - 0x54]; struct CueRef first; struct CueRef second;
};
void func_00244CA8(void *sound, float value);
void func_002BBCD8(void *reference, void *value);
void func_00166548(void *pose);
void func_00169E40(void *self);
void func_0016B0D0(struct CueSelf *self)
{
    struct CueRef *reference = &self->first;
    if(reference && reference->object) {
        func_00244CA8(reference->object, 0.0f);
        func_002BBCD8(reference, 0);
    }
    reference = &self->second;
    if(reference && reference->object) {
        func_00244CA8(reference->object, 0.5f);
        func_002BBCD8(reference, 0);
    }
    self->clear20 = 0;
    self->clear24 = 0;
    self->rate = -1.0f;
    self->clear50 = 0;
    func_00166548(self->pose);
    func_00169E40(self);
}
