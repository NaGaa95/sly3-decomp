// SLY3_CFLAGS: -Os -G0
void func_0028FD70(void *self);
void func_0011AF38(void *list,int offset);
void func_001C9118(void *self,int state);
struct InitSelf { unsigned char prefix[0x3C]; unsigned int tagged; unsigned char gap40[0xE0-0x40]; int wordE0; int wordE4; float fE8; float fEC; unsigned char gapF0[0xF8-0xF0]; int wordF8; unsigned char gapFC[0x124-0xFC]; float f124; };
void func_00177520(struct InitSelf *self)
{
    unsigned int value;
    func_0028FD70(self);
    self->wordE0=1;
    self->wordE4=-1;
    self->fEC=10.0f;
    self->fE8=10.0f;
    self->wordF8=-1;
    self->f124=-1.0f;
    func_0011AF38((char *)self+0xFC,0x108);
    func_001C9118(self,0);
    value=self->tagged;
    if((value^1)&1)*(unsigned int *)value|=2;
    else self->tagged=value|2;
}
