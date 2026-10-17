// SLY3_CFLAGS: -Os -G0
extern int D_0036DBE0;
struct ModeEntry { short delta,padding; int (*fn)(void *); };
struct ModeChild { struct ModeEntry *table; };
struct ModeOwner { unsigned char prefix[0x1450]; struct ModeChild *child; };
void func_0021F5D0(int index,int enabled);
void func_001548E8(void *owner,int a,int index);
int func_001F4458(void *owner);
void func_001F4438(void *owner,int value);
void func_00154AB8(struct ModeOwner *owner)
{
    struct ModeChild *child;
    int index;
    int notmode=(D_0036DBE0!=2);
    if(notmode) return;
    child=owner->child;
    if(!child) return;
    index=child->table[1].fn((char *)child+child->table[1].delta);
    func_0021F5D0(index,1);
    func_001548E8(owner,0,index);
    func_001F4438(owner,func_001F4458(owner));
}
