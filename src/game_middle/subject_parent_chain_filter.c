// SLY3_CFLAGS: -Os -G0
struct KindFlags { unsigned char opaque[0x70]; unsigned long flags; };
struct ChainNode { unsigned char opaque00[0x10]; struct ChainNode *parent; int group14; unsigned char opaque18[0xC4]; struct KindFlags *kind; };
struct Subject { unsigned char opaque00[4]; struct ChainNode *node; unsigned char opaque08[0x10]; unsigned long flags; };
struct Gate { unsigned char opaque[0x14]; int group; };
int func_0013B500(void *object, int identifier);
int func_001B4210(struct Gate *gate, struct Subject *subject)
{
    struct ChainNode *node;
    if (subject->flags & 0x10000)
        return 0;
    if (subject->node->kind->flags & 4)
        return 0;
    if (subject->node->group14 == gate->group)
        return 0;
    for (node = subject->node; node; node = node->parent) {
        if (func_0013B500(node, 0x32))
            break;
    }
    return node == 0;
}
