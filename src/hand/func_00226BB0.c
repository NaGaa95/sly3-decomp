// Look up the explicit owner through the parent chain and return its value, or zero when absent.
// Reference algorithm: src/hand/func_0015EF00.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -O2 -G0
struct R { char pad[0x1008]; int value; };
struct R *func_00226B78(void *owner);
int func_00226BB0(void *owner)
{
    int value;
    struct R *record = func_00226B78(owner);
    value = 0;
    if (record) value = record->value;
    return value;
}
