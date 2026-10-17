// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[];
struct SoundRec { int base; unsigned char count; unsigned char cursor; unsigned char pad[2]; };
struct SoundEntry { unsigned char prefix[0x28]; int sound; struct SoundRec recs[2]; unsigned char tail[0x3C-0x3C]; };
extern struct SoundEntry D_00343098[];
struct SoundObject { unsigned char prefix[0x120]; int word120; int word124; };
struct SoundSelf { unsigned char prefix[0x130]; int slot; unsigned char gap134[0x438-0x134]; int index; unsigned char gap43C[0x440-0x43C]; int word440; int word444; struct SoundObject *object; int current; };
void func_00262B60(void *object,int sound,int *current);
void *func_002485D8(void *context,int item,int flag,void *child);
void func_00142650(struct SoundSelf *self)
{
    struct SoundEntry *entry;
    int sound,item;
    if(!self->object) return;
    self->object->word120=self->word440;
    self->object->word124=self->word444;
    if(self->index==-1) { self->current=0x7AF; return; }
    entry=&D_00343098[self->index];
    sound=0x7AF;
    if((unsigned int)(entry->sound+1)>=2) sound=entry->sound;
    item=-1;
    if(self->slot!=-1) {
        struct SoundRec *rec=&entry->recs[self->slot];
        if(rec->count) {
            int cursor=rec->cursor;
            item=rec->base+cursor;
            rec->cursor=(cursor+1)%rec->count;
        }
    }
    if(sound!=self->current) {
        func_00262B60(self->object,sound,&self->current);
        if(item!=-1) func_002485D8(D_00474FF0,item,1,0);
    }
}
