// Store a value into the attached node when its kind is 0x15.
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

void func_00226320(struct Holder *holder, int value)
{
    struct Node *node = holder->node;
    if (node && node->kind->type == 0x15) node->value = value;
}
