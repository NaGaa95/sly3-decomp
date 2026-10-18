// SLY3_CFLAGS: -Os -G0
struct KindGate {
    void *owner;
    int value;
    unsigned char gap8[0x1C - 8];
    int kind;
};
int func_00156700(void *);
int func_00176D40(void *, void *);
int func_001BAD30(struct KindGate *gate, void *request)
{
    if (func_00156700(gate->owner))
        return 0;
    switch (gate->kind) {
    case 1:
    case 3: case 4: case 5: case 6: case 7:
        break;
    default:
        return 0;
    }
    if (gate->value < 16) {
        if (gate->value >= 14)
            return 0;
    }
    return func_00176D40(gate->owner, request);
}
