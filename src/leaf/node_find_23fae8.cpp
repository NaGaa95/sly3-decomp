// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" void func_002BBEC8(void *,int);
struct Guard { ~Guard() { func_002BBEC8(this,2); } };
struct Owner { unsigned char prefix[0x18]; int id; };
struct Node { unsigned char prefix[0x14]; Owner *owner; void *key; unsigned char gap1C[8]; Node *next; };
extern "C" unsigned char D_00479994[];
extern "C" Node *func_0023FAE8(void *key,int ownerId)
{
    Guard guard;
    for(Node *node=*(Node **)D_00479994;node;node=node->next) {
        if(node->key==key && (ownerId==-1 || node->owner->id==ownerId))
            return node;
    }
    return 0;
}
