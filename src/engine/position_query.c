// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct QueryEntry { short delta,padding; char *(*fn)(void *); };
struct QueryOwner { unsigned char prefix[0xC]; struct QueryEntry *table; void *handle; unsigned char gap14[0x120-0x14]; char *record; };
struct QuerySelf { unsigned char prefix[0x10]; struct QueryOwner *owner; };
struct QueryActor { unsigned char prefix[0x28]; unsigned long flags; };
struct QueryPair { Qword a; Qword b; };
extern struct QueryActor *D_00370AC0;
int func_001C0B70(void *actor,struct QueryPair *out,int mode);
Qword func_001C03A0(void *actor,struct QueryPair *in,float value);
Qword func_001C9428(void *source,void *destination,Qword point);
Qword func_0015FB28(struct QuerySelf *self)
{
    struct QueryPair temp;
    if(D_00370AC0) {
        int flagged=(D_00370AC0->flags&(1UL<<56))!=0;
        if(flagged) {
            if(func_001C0B70((char *)D_00370AC0+0xA20,&temp,5)) return func_001C03A0(D_00370AC0,&temp,0.0f);
            return *(Qword *)(self->owner->table[36].fn((char *)self->owner+self->owner->table[36].delta)+0x30);
        }
    }
    return func_001C9428(self->owner->handle,0,*(Qword *)(self->owner->record+0x30));
}
