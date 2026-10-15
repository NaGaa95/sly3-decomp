// Dispatch the original state2/3 enabled values, preserving the inactive/default states.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Receiver {
    char prefix[0x1C];
    int state;
};
void func_00210ED8(void *receiver, int enabled);
void func_00210F60(struct Receiver *p) {
    switch (p->state) {
        case 1: break;
        case 2: func_00210ED8(p, 1);
        break;
        case 3: func_00210ED8(p, 0);
        break;
    }
}
