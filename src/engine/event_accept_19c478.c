// SLY3_CFLAGS: -Os -G0
struct AcceptEntry { short delta; short pad; int (*method)(void *,int); };
struct AcceptTable { unsigned char prefix[0x280]; struct AcceptEntry entry; };
struct AcceptSource { unsigned char prefix[0x14]; struct AcceptSource *peer; unsigned char gap18[0x20-0x18]; int word20; };
struct AcceptSelf {
    unsigned char prefix[0xC]; struct AcceptTable *table;
    unsigned char gap10[0x1D0-0x10]; int identity;
    unsigned char gap1D4[0x1F0-0x1D4]; int state;
};
extern unsigned char D_0036C700[];
int func_0013B500(void *object,int identifier);
int func_0019B6E0(void *self,void *event);
int func_001F43C8(void *self);
void func_001854C8(void *context,int event,void *owner);
void func_0019C570(void *owner,int state);
int func_0019C478(struct AcceptSelf *self,void *event)
{
    struct AcceptSource *source=event;
    if(self->state<7) {
        if(self->state>=2) return 0;
    }
    if(self->table->entry.method((char *)self+self->table->entry.delta,source->word20)) return 0;
    if(func_0013B500(source->peer,0x4C)) {
        if(*(int *)((char *)source->peer+0x1D0)==self->identity) return 0;
    }
    if(!func_0019B6E0(self,event)) return 0;
    if(func_001F43C8(self)>0) {
        func_001854C8(D_0036C700,0xA,self);
        func_0019C570(self,2);
    }
    return 1;
}
