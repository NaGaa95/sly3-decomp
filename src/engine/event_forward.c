// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct FwdEntry { short delta,padding; void (*fn)(void *); };
struct FwdEvent { unsigned char prefix[0xC]; struct FwdEntry *table; unsigned char gap10[0x38-0x10]; int word38; unsigned char gap3C[0x44-0x3C]; float f44; unsigned char gap48[0xA0-0x48]; int wordA0; unsigned char gapA4[0xBC-0xA4]; int wordBC; float fC0; };
struct FwdSelf { unsigned char prefix[0x10]; char *owner; unsigned char gap14[0x30-0x14]; int word30; float f34; int word38; float f3C; Qword vector; int word50; };
void func_00238978(void);
struct FwdEvent *func_00238690(void *owner,int kind);
void func_00157970(void *self,Qword vector);
void func_001578C8(struct FwdSelf *self)
{
    struct FwdEvent *event;
    func_00238978();
    event=func_00238690(self->owner+0x29C,0xEF);
    event->word38=self->word30;
    event->f44=self->f34;
    event->wordBC=self->word38;
    event->fC0=self->f3C;
    event->wordA0=self->word50;
    func_00157970(self,self->vector);
    event->table[8].fn((char *)event+event->table[8].delta);
}
