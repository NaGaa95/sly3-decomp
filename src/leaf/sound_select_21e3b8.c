// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[];
extern int D_0036DBE0;
struct SoundRec { int base; unsigned char count; unsigned char cursor; unsigned char pad[2]; };
struct SoundEntry { unsigned char prefix[0x28]; int sound; struct SoundRec recs[2]; unsigned char tail[0x3C-0x3C]; };
extern struct SoundEntry D_00343098[];
struct SoundOwner { unsigned char prefix[0x130]; int slot; unsigned char gap134[0x1250-0x134]; int word1250; unsigned char gap1254[0x18B0-0x1254]; int word18B0; };
struct SoundSelf { unsigned char prefix[0x138]; int mode; struct SoundOwner *owner; unsigned char gap140[4]; int current; };
int func_0013B500(void *object,int kind);
void func_00262B60(void *object,int sound,int *current);
void *func_002485D8(void *context,int item,int flag,void *child);
void func_0021E3B8(struct SoundSelf *self)
{
    int index,sound,item,mode;
    struct SoundEntry *entry;
    if((unsigned int)(self->mode+1)<2) return;
    if(func_0013B500(self->owner,0x33)) index=self->owner->word1250;
    else if(func_0013B500(self->owner,0x3C)) index=self->owner->word18B0;
    else index=-1;
    sound=0x7AF;
    item=-1;
    mode=D_0036DBE0^2;
    if(!mode && index!=-1) {
        int slot=self->owner->slot;
        entry=&D_00343098[index];
        if((unsigned int)(entry->sound+1)>=2) sound=entry->sound;
        if(slot!=-1) {
            struct SoundRec *rec=&entry->recs[slot];
            if(rec->count) {
                int cursor=rec->cursor;
                item=rec->base+cursor;
                rec->cursor=(cursor+1)%rec->count;
            }
        }
    }
    if(sound!=self->current) {
        func_00262B60(self,sound,&self->current);
        if(item!=-1) func_002485D8(D_00474FF0,item,1,0);
    }
}
