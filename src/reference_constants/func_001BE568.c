// Reference algorithm: src/hand/func_001492B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024BCC0(void *); void func_001BECB8(void *,void *); void func_001BE568(char *p) { void *entry = *(void **)(p + 0x14); if(entry) func_0024BCC0(entry); func_001BECB8(p, *(void **)(p + 0xC)); }
