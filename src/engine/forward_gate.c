// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct GateRoot { unsigned char prefix[0x70]; Qword vector; };
struct GateSelf { struct GateRoot *root; unsigned char gap4[8-4]; float amount; unsigned char gapC[0x18-0xC]; unsigned long flags; };
int func_00119BE8(void *object,int limit,Qword origin,Qword direction,void *output,int flags);
int func_00164B08(Qword base,Qword origin,Qword direction,void *output,int flags,float amount);
int func_00164A98(struct GateSelf *self,void *object,Qword origin,Qword direction,void *output,int flags)
{
    if(object) return func_00119BE8(object,0x7FFFFFFF,origin,direction,output,flags);
    if(self->flags&0x20000) return func_00164B08(self->root->vector,origin,direction,output,flags,self->amount);
    return 0;
}
