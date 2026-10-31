// Return the value of the attached node when its kind is 0x15, otherwise 0.
// SLY3_CFLAGS: -Os -G0
struct NodeKind { unsigned char type; };
struct Node {
    char opaque00[0x1C];
    int value;
    char opaque20[0x14];
    struct NodeKind *kind;
};
struct Holder {
    char opaque00[0x54];
    struct Node *node;
};

int func_002262F0(struct Holder *holder)
{
    struct Node *node = holder->node;
    if (!node || node->kind->type != 0x15) return 0;
    return node->value;
}
