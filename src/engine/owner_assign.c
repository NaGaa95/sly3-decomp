// SLY3_CFLAGS: -Os -G0
extern char D_00474FF0[];
struct AssignEntry { short delta,padding; void (*fn)(void *,int,int); };
struct AssignChild { unsigned char prefix[0xC]; struct AssignEntry *table; };
struct AssignOwner { unsigned char prefix[0x48]; int word48; struct AssignChild *child; };
void *func_002485D8(void *context,int word,int flag,void *child);
void func_00244F08(void *record,void *child);
void func_0018C0F8(struct AssignOwner *owner,int word,struct AssignChild *child)
{
    owner->word48=word;
    owner->child=child;
    if(child) child->table[94].fn((char *)child+child->table[94].delta,0x20,0);
    func_00244F08(func_002485D8(D_00474FF0,owner->word48,0,child),child);
}
