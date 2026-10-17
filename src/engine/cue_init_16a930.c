// SLY3_CFLAGS: -Os -G0
struct CueEntry { short delta; short pad; void *(*method)(void *); };
struct CueOwner { unsigned char prefix[0xC]; struct CueEntry *table; unsigned char gap10[0x11C-0x10]; float scale; };
struct CueSelf {
    struct CueOwner *owner; unsigned char gap4[0xB4-4];
    float pan; float tilt; float clearBC; float clearC0; float divisor; float ratio; float scaleCopy;
    void *first; void *second;
};
void func_00169E28(void *self);
void *func_002459F8(int identifier);
void func_00244F08(void *voice,void *owner);
void func_002BBCD8(void *reference,void *value);
void func_00244C28(void *voice);
void func_0011D048(void *record,float *first,float *second);
void func_001679E0(void *owner,float value);
void func_0016AE90(void *self);
void func_00168670(void *owner,int mode);
void func_0016A930(struct CueSelf *self)
{
    void *voice;
    func_00169E28(self);
    voice=func_002459F8(0x26);
    func_00244F08(voice,0);
    func_002BBCD8(&self->first,voice);
    voice=func_002459F8(0x25);
    func_00244F08(voice,0);
    func_002BBCD8(&self->second,voice);
    func_00244C28(self->first);
    func_0011D048(self->owner->table[36].method((char *)self->owner+self->owner->table[36].delta),&self->pan,&self->tilt);
    self->tilt=0;
    self->clearBC=0;
    self->clearC0=0;
    self->ratio=self->owner->scale/self->divisor;
    self->scaleCopy=self->owner->scale;
    func_001679E0(self->owner,49.0f);
    func_0016AE90(self);
    func_00168670(self->owner,2);
}
