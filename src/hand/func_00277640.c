// Classify the original Sly 3 state range through its complete thirteen-entry dispatch table.
// Reference algorithm: src/hand/func_001ACC80.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
struct S { char prefix[0x13C]; int state; };
int func_00277640(struct S *object)
{
    static void *const states[] __attribute__((aligned(4))) = { &&true_state,&&false_state,&&true_state,&&false_state,&&true_state,&&false_state,&&true_state,&&false_state,&&false_state,&&true_state,&&false_state,&&true_state,&&true_state };
    unsigned int state = object->state - 4;
    if (state >= 13) goto false_state;
    goto *states[state];
false_state:
    return 0;
true_state:
    return 1;
}
