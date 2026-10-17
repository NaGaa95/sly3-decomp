// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
extern "C" void func_002BFCF8(void *,int);
struct Guard { ~Guard() { func_002BFCF8(this,2); } };
struct Node { int key; int value; Node *next; };
struct Owner { char prefix[0x4964]; Node *head; };
extern "C" int func_0025DD38(Owner *owner,int key,int value)
{
    Guard guard;
    if(!key)
        return 0;
    for(Node *node=owner->head;node;node=node->next)
        if(node->key==key && node->value==value)
            return 1;
    return 0;
}
