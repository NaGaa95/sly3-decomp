// SLY3_CFLAGS: -Os -G0
struct NoteEntry { short delta,padding; void (*fn)(void *,int,int,int,int,int); };
struct NoteEnd { void *object; unsigned char rest[0x3C]; };
struct NoteLink { unsigned char prefix[8]; struct NoteEnd ends[2]; unsigned char gap88[0xAC-0x88]; struct NoteLink *next; };
struct NoteEndView { unsigned char pre[8]; void *object; };
struct NoteList { struct NoteLink *links; struct NoteList *next; };
struct NoteGroup { unsigned char prefix[0x64]; struct NoteList *lists; };
struct NoteSelf { unsigned char prefix[0xC]; struct NoteEntry *table; unsigned char gap10[0xDC-0x10]; struct NoteGroup *group; unsigned char gapE0[0x15C-0xE0]; void *current; };
void func_001393E8(struct NoteSelf *self)
{
    void *found[16];
    int count=0;
    int i;
    struct NoteList *list;
    for(list=self->group->lists;list;list=list->next) {
        struct NoteLink *link;
        for(link=list->links;link;link=link->next) {
            int which=(link->ends[0].object==(void *)self);
            void *other=((struct NoteEndView *)((char *)link+(which<<6)))->object;
            for(i=0;i<count;i++) if(other==found[i]) break;
            if(i>=count) {
                found[count++]=other;
                if(!(count>=0 && count<16)) goto collected;
            }
        }
    }
collected:
    for(i=0;i<count;i++) {
        self->current=found[i];
        self->table[3].fn((char *)self+self->table[3].delta,5,0,0,0,0);
    }
}
