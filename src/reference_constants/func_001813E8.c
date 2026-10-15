// Reference algorithm: src/hand/func_00149220.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Word { int value; } __attribute__((packed)); void func_001813E8(char *p,struct Word *source) { *(struct Word *)(p + 0x16C) = *source; *(struct Word *)(p + 0x164) = *(struct Word *)(p + 0x16C); }
