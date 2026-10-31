// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Node {
    unsigned char pad0[0x44]; int state;
    unsigned char pad48[0x6C - 0x48]; struct Node *group;
    unsigned char pad70[0x84 - 0x70]; int count; struct Node **children;
    unsigned char pad8C[0xF8 - 0x8C]; int lock;
};
void func_001899F0(struct Node *node, int mode, int *count, struct Node **out)
{
    int i;
    for (i = 0; i < node->count; i++) {
        struct Node *child = node->children[i];
        int need = -1;
        switch (mode) {
        case 0:
            break;
        case 1:
        case 2:
            {
                struct Node *group = child->group;
                if (group && (group == node->group || group->group))
                    need = 2;
                else
                    need = 3;
            }
            break;
        case 3:
            need = 3;
            break;
        }
        if (child->lock == -1 && child->state < need) {
            func_001899F0(child, need, count, out);
        }
    }
    out[(*count)++] = node;
    node->lock = mode;
}
