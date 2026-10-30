// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Node {
    unsigned char pad0[0x44]; int state;
    unsigned char pad48[0x6C - 0x48]; int group;
    unsigned char pad70[0x84 - 0x70]; int count; struct Node **children;
    unsigned char pad8C[0xF8 - 0x8C]; int lock;
};
void func_0018A670(struct Node *node, int state);
void func_0018A778(struct Node *node, int mode)
{
    int state, next;
    if (node->lock != -1) return;
    state = node->state;
    next = state;
    if (mode >= 0) {
        if (mode < 2) {
            next = 0;
        } else if (mode < 4) {
            int ok = 1, all = 1, i;
            for (i = 0; i < node->count; i++) {
                struct Node *child = node->children[i];
                if (child->state < 2) { ok = 0; all = 0; break; }
                if (child->state < 3 || child->group != node->group || child->group == 0) all = 0;
            }
            if (!ok) next = 0;
            else if (mode == 3 && all) next = 3;
            else switch (node->state) {
            case 0: next = 1; break;
            case 1: case 2: next = state; break;
            case 3: next = mode; break;
            }
        }
    }
    func_0018A670(node, next);
}
