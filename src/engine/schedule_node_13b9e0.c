// SLY3_CFLAGS: -Os -G0
struct ScheduledScript {
    short tag;
    unsigned short references;
};
struct ScheduledNode {
    float deadline;
    void *recipient;
    struct ScheduledScript *script;
    int serial;
    struct ScheduledNode *next;
};
struct SchedulingOwner {
    unsigned char prefix[0x3F2C];
    unsigned char pool[24];
};
struct SchedulingSerial {
    unsigned char prefix[0x4508];
    unsigned int serial;
};
struct SchedulingList {
    struct ScheduledNode *head;
    struct ScheduledNode *tail;
    int linkOffset;
};
extern struct SchedulingSerial D_00475480;
extern struct SchedulingList D_004793A0;
struct ScheduledNode *func_0011E118(void *pool);
void func_0011ADD0(struct SchedulingList *list,struct ScheduledNode *previous,struct ScheduledNode *node);

struct ScheduledNode *func_0013B9E0(struct SchedulingOwner *owner,void *recipient,struct ScheduledScript *script,float deadline)
{
    struct ScheduledNode *node;
    struct ScheduledNode *previous;
    struct ScheduledNode *current;
    int serial;
    script->references++;
    node=func_0011E118(owner->pool);
    node->recipient=recipient;
    if(!recipient)
        serial=(int)++D_00475480.serial;
    else
        serial=-1;
    node->serial=serial;
    node->script=script;
    node->deadline=deadline;
    node->next=0;
    previous=0;
    for(current=D_004793A0.head;current;current=current->next) {
        if(current->deadline>node->deadline)
            break;
        previous=current;
    }
    func_0011ADD0(&D_004793A0,previous,node);
    return node;
}
