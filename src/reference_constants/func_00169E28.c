// Reference algorithm: src/hand/func_00221120.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00169E28(char *p) { char *owner = *(char **)p; *(float *)(p + 0x18) = *(float *)(owner + 0x144); *(float *)(p + 0x14) = *(float *)(owner + 0x11C); }
