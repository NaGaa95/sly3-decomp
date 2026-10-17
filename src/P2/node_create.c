// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Node { unsigned char prefix[0x20]; unsigned char first[0x10]; unsigned char second[0x10]; int word40; int word44; void *owner; unsigned char gap4C[4]; };
void *func_001C9A50(unsigned int bytes);
void *func_002BF168(void *object);
void func_0022EA88(void *owner,qword position,int mode,void *first,void *second,void *third,void *fourth);
struct Node *func_0022F2E0(void *owner,qword position)
{
    struct Node *node=func_002BF168(func_001C9A50(0x50));
    func_0022EA88(owner,position,0,node->first,node->second,&node->word44,&node->word40);
    node->owner=owner;
    return node;
}
