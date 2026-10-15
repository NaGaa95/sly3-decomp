// Complete cleanup consumes receiver A0 only.24E2B8->243738 consumes only incoming receiver before explicit internal float/vector call setup;238828 consumes embedded29C record A0 and explicitly sets its virtual receiver. Both actual helper inputs are explicit.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
void func_0024E2B8(void *receiver);
void func_00238828(void *record);
void func_00257548(void *receiver){func_0024E2B8(receiver);func_00238828((char *)receiver+0x29C);}
