// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[];
extern int D_0047A424;
extern float D_0036BB98;
struct SoundRec { int base; unsigned char count; unsigned char cursor; unsigned char pad[2]; };
struct SoundEntry { unsigned char prefix[0x28]; int sound; struct SoundRec recs[2]; unsigned char tail[0x3C-0x3C]; };
extern struct SoundEntry D_00343098[];
struct SoundOwner {
    unsigned char prefix[0x130]; int slot;
    unsigned char gap134[0x1B8-0x134]; int kind;
    unsigned char gap1BC[0x1D0-0x1BC]; struct SoundOwner *source;
    unsigned char gap1D4[0x4F4-0x1D4]; int index; float start; float length;
};
struct SoundSelf { unsigned char prefix[0x138]; int mode; struct SoundOwner *owner; unsigned char gap140[4]; int current; int fallback; };
void func_00262B60(void *object,int sound,int *current);
void func_00262450(void *object,int sound);
void func_00261528(void *receiver,int identifier,float numerator,float denominator);
void *func_002485D8(void *context,int item,int flag,void *child);
void func_0021BA40(struct SoundSelf *self)
{
    int sound,item;
    if((unsigned int)(self->mode+1)<2) return;
    sound=self->fallback;
    item=-1;
    if(D_0047A424) {
        struct SoundOwner *owner=self->owner;
        int index=owner->index;
        if(index!=-1) {
            struct SoundEntry *entry=&D_00343098[index];
            int slot=-1;
            if((unsigned int)(entry->sound+1)>=2) sound=entry->sound;
            switch(owner->kind) {
            case 0:
                slot=owner->slot;
                break;
            case 1:
                if(owner->source) slot=owner->source->slot;
                break;
            }
            if(slot!=-1) {
                struct SoundRec *rec=&entry->recs[slot];
                if(rec->count) {
                    int cursor=rec->cursor;
                    item=rec->base+cursor;
                    rec->cursor=(cursor+1)%rec->count;
                }
            }
        }
    }
    if(sound!=self->current) {
        func_00262B60(self,sound,&self->current);
        if(sound!=self->fallback) func_00262450(self,0x794);
        if(item!=-1) func_002485D8(D_00474FF0,item,1,0);
    }
    if(sound!=self->fallback) func_00261528(self,0x794,self->owner->length-(D_0036BB98-self->owner->start),self->owner->length);
}
