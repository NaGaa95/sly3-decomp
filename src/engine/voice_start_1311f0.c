// SLY3_CFLAGS: -Os -G0
struct VoiceRow { int identifier; float low; float high; float volume; float pitch; float value; };
struct VoiceOwner {
    unsigned char prefix[0xD0]; int count; struct VoiceRow *rows; void **voices;
};
void func_001C85E8(void *owner);
void *func_002459F8(int identifier);
void func_00244F08(void *voice,void *owner);
void func_00245100(void *voice,float low,float high);
void func_00244E08(void *voice,float volume);
void func_00244ED0(void *voice,float pitch);
void func_00245130(void *voice,float value);
void func_002BBCD8(void *reference,void *value);
void func_001311F0(struct VoiceOwner *self)
{
    int i;
    func_001C85E8(self);
    for(i=0;i<self->count;i++) {
        struct VoiceRow *row=&self->rows[i];
        void *voice=func_002459F8(row->identifier);
        func_00244F08(voice,self);
        func_00245100(voice,row->low,row->high);
        func_00244E08(voice,row->volume);
        func_00244ED0(voice,row->pitch);
        func_00245130(voice,row->value);
        func_002BBCD8((void **)((i<<2)+(int)self->voices),voice);
    }
}
