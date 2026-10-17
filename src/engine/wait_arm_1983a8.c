// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int tag; int payload; } CRef;
struct Mask { unsigned int words[4]; };
struct MaskRef { int kind; struct MaskRef *link; int word8; int wordC; };
struct WaitArm { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x4C-0x14]; int identifier; int value; int mode; };
struct Mask *func_00252AD0(struct Mask *output,int bit);
struct MaskRef *func_00255418(void *table,const struct Mask *mask);
CRef *func_0024AEF8(CRef *output,int count,int type,void *values);
void func_002534C0(void *owner,CRef *reference,int value,int mode);
void func_0012BC20(CRef *reference);
void func_001983A8(struct WaitArm *self,int identifier,int value,int mode)
{
    union { struct Mask mask; CRef reference; } scratch;
    struct MaskRef *record;
    func_00252AD0(&scratch.mask,identifier);
    record=func_00255418(self->owner,&scratch.mask);
    if(record) {
        switch(record->kind) {
        case -1:
            self->value=(int)record->link;
            break;
        case 0:
            self->value=*(int *)((char *)record->link+0x18);
            break;
        case 1:
            self->value=*(int *)((char *)record->link+0x18);
            break;
        }
        self->identifier=identifier;
        self->mode=record->wordC;
        func_0024AEF8(&scratch.reference,1,0x100F,&identifier);
        func_002534C0(self->owner,&scratch.reference,value,mode);
        func_0012BC20(&scratch.reference);
    }
}
