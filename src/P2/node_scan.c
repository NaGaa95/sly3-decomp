// SLY3_CFLAGS: -Os -G0
struct Node {
    int word0;
    struct Node *next;
    int flag;
};
struct Method {
    short delta;
    short unused;
    void (*call)(void *, void *);
};
struct Owner {
    unsigned char prefix[0xC];
    struct Method *methods;
    unsigned char gap[0xD8 - 0x10];
    struct Node *nodes;
};
void func_001FB710(struct Owner *, struct Node *);
int func_001FC7D0(struct Owner *owner, void *argument)
{
    int found = 0;
    struct Node *node = owner->nodes;
    while (node) {
        struct Node *next = node->next;
        if (node->flag)
            found = 1;
        else
            func_001FB710(owner, node);
        node = next;
    }
    if (!found)
        owner->methods[32].call((char *)owner + owner->methods[32].delta, argument);
    return !found;
}
