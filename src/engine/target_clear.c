// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct ClearTarget { unsigned char prefix[0x324]; int word324; unsigned char gap328[0x33C-0x328]; int word33C; float f340; };
struct ClearRecord { int a; int b; int c; };
struct ClearSelf { unsigned char prefix[0x130]; unsigned char sub[0x144-0x130]; struct ClearTarget *target; unsigned char gap148[0x240-0x148]; struct ClearRecord record; };
int func_0013B500(void *object,int kind);
void func_0015C178(void *sub,int flag);
void func_0015CAD0(struct ClearSelf *self)
{
    if(func_0013B500(self->target,0x33)) {
        struct ClearTarget *target=self->target;
        if(target->word33C==0x12) { self->target=0; return; }
        if(target->word324==3 && D_0036BB98.t-target->f340<0.15f) { self->target=0; return; }
    }
    func_0015C178(self->sub,1);
    {
        struct ClearRecord *record=&self->record;
        record->c=0;
        record->b=0;
        self->record.a=0;
    }
}
