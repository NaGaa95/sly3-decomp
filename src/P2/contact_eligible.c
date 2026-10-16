// SLY3_CFLAGS: -Os -G0
struct ContactObject;
struct ContactNode;
struct ContactVirtualEntry { short delta; short unused; void *method; };
struct ContactObject { char prefix[12]; struct ContactVirtualEntry *vtable; };
struct ContactPair { void *resource; struct ContactPair *next; struct ContactPair *other; struct ContactObject *object; };
struct ContactNode { char prefix[0x58]; struct ContactNode *next; int word5C; struct ContactObject *object; struct ContactPair *pairs; void *resource; int word6C; unsigned long flags; };
struct ContactBinding { char prefix[0xDC]; struct ContactNode *node; };
struct ContactGame { char prefix[0x44D0]; struct ContactNode *first; };
struct ContactCandidate {
    int unused;
    struct ContactBinding *binding;
    unsigned char gap[0x18-8];
    unsigned long flags;
};
int func_0013CD00(int,int);
#define CONTACT_QUERY(object,other) ((int (*)(void *,struct ContactObject *))(object)->vtable[65].method)((char *)(object)+(object)->vtable[65].delta,(other))
int func_0025CDD0(void *receiver,void *rawEntry)
{
    struct ContactNode *node=(struct ContactNode *)receiver;
    struct ContactCandidate *entry=(struct ContactCandidate *)rawEntry;
    struct ContactNode *other=entry->binding->node;
    int first,second,result;
    if(!(entry->flags&0x10000UL) && (other->flags&4)) return 0;
    if((entry->flags&0x10000UL) || other==node) return 0;
    first=CONTACT_QUERY(node->object,other->object);
    second=CONTACT_QUERY(other->object,node->object);
    result=func_0013CD00(first,second);
    return result!=1 && result!=3;
}
