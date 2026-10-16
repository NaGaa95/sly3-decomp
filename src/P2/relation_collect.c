// SLY3_CFLAGS: -Os -G0
struct RelationSubject;
struct RelationNode {
    int enabled;
    struct RelationNode *next;
    int unused;
    struct RelationSubject *subject;
};
struct RelationList { unsigned char beforeFirst[0x64]; struct RelationNode *first; };
struct RelationProperties {
    unsigned char beforeSubtype[0xA0];
    int subtype;
    unsigned char beforeKind[0xC0-0xA4];
    int kind;
};
struct RelationSubject {
    unsigned char beforeProperties[0xD8];
    struct RelationProperties *properties;
    struct RelationList *links;
    unsigned char beforeFlags[0x120-0xE0];
    unsigned long flags;
};
void func_00242AA8(void *context,struct RelationSubject *subject,int *count,
                   struct RelationSubject **output)
{
    struct RelationNode *node;
    subject->flags|=0x0800000000000000UL;
    output[*count]=subject;
    (*count)++;
    for (node=subject->links->first;node;node=node->next) {
        struct RelationSubject *other;
        struct RelationProperties *properties;
        if (!node->enabled) continue;
        other=node->subject;
        if (other->flags&0x0800000000000000UL) continue;
        properties=other->properties;
        if (!properties) continue;
        if (properties->kind==3 && properties->subtype==3) continue;
        func_00242AA8(context,other,count,output);
    }
}
