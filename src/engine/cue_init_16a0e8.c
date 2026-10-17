// SLY3_CFLAGS: -Os -G0
struct CueEntry { short delta; short pad; void *(*method)(void *); };
struct CueOwner { unsigned char prefix[0xC]; struct CueEntry *table; unsigned char gap10[0x11C - 0x10]; float scale; };
struct Pair8 { int a; int b; };
struct CueSelf {
    struct CueOwner *owner; unsigned char gap4[0x20 - 4]; void *target;
    float pan; float tilt; float clear2C; float clear30; float clear34; float clear38; float divisor; float ratio; float scaleCopy;
    void *first; void *second; struct Pair8 flagA; struct Pair8 flagB;
};
extern const struct Pair8 D_00320E80, D_00320E88;
void func_00169E28(void *self);
void *func_002459F8(int identifier);
void func_00244F08(void *voice, void *owner);
void func_002BBCD8(void *reference, void *value);
void func_00244C28(void *voice);
void func_0011D048(void *record, float *first, float *second);
int func_0013B500(void *object, int identifier);
void func_001679E0(void *owner, float value);
void func_00168670(void *owner, int mode);
void func_0016A0E8(struct CueSelf *self)
{
    func_00169E28(self);
    {
        void *voice = func_002459F8(0x26);
        func_00244F08(voice, 0);
        func_002BBCD8(&self->first, voice);
    }
    {
        void *voice = func_002459F8(0x25);
        func_00244F08(voice, 0);
        func_002BBCD8(&self->second, voice);
    }
    func_00244C28(self->first);
    func_0011D048(self->owner->table[36].method((char *)self->owner + self->owner->table[36].delta), &self->pan, &self->tilt);
    if(func_0013B500(self->target, 0x33)) {
        self->flagA = D_00320E80;
        self->flagB = D_00320E88;
    }
    self->clear2C = 0;
    self->clear30 = 0;
    self->clear34 = 0;
    self->clear38 = 0;
    self->ratio = self->owner->scale / self->divisor;
    self->scaleCopy = self->owner->scale;
    func_001679E0(self->owner, 49.0f);
    func_00168670(self->owner, 1);
}
