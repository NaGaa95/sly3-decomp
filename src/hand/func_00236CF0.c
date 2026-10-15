// Original signed-key, open-addressed lookup from the Sly 2 reference algorithm.
// The node declaration is only its proven key prefix; the return is a real record pointer.
// Original loop branch/division delay and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Node {
    int key;
};
extern struct Node **D_00474FC0;
struct Node *func_00236CF0(int key) {
    int index;
    struct Node *node;
    if (!D_00474FC0)
        return 0;
    index = key % 0x3FFD;
    loop:
    node = D_00474FC0[index];
    if (!node || node->key == key)
        return node;
    index = (index + 1) % 0x3FFD;
    goto loop;
}
