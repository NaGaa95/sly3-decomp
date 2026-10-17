// SLY3_CFLAGS: -Os -G0
int func_00185A08(void *object);
struct AppendEntry { int word0; int word4; int word8; int wordC; int word10; };
struct AppendOwner { unsigned char prefix[0x40]; int locked; unsigned char gap44[0x98-0x44]; int count; struct AppendEntry *entries; };
void func_00188118(struct AppendOwner *owner,int word0,void *object,int word4,int wordC,int word10)
{
    if(!owner->locked) {
        if(owner->count<0x20) {
            struct AppendEntry *entry=&owner->entries[owner->count++];
            entry->word0=word0;
            entry->word4=word4;
            entry->word8=func_00185A08(object);
            entry->wordC=wordC;
            entry->word10=word10;
        }
    }
}
