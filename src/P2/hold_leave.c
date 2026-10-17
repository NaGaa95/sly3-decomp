// SLY3_CFLAGS: -Os -G0
struct Link { unsigned char prefix[0x14]; struct Link *next; unsigned char gap18[8]; int count; };
struct Holder { unsigned char prefix[0x10]; void *target; struct Link *links; int unknown_18; int active; };
int func_0013B500(void *target,int kind);
void func_00257230(void *target);
void func_00238A38(struct Holder *holder)
{
    struct Link *link;
    if(!holder->active)
        return;
    holder->active=0;
    if(func_0013B500(holder->target,0x3A))
        func_00257230(holder->target);
    for(link=holder->links;link;link=link->next)
        link->count--;
}
