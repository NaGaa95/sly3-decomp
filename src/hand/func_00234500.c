// Return whether the original global low-two-bit state is clear.
// Reference algorithm: src/hand/func_001F5860.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern unsigned int D_0036DBEC;
int func_00234500(void)
{
    return (D_0036DBEC & 3)==0;
}
