// Reference algorithm: src/hand/func_001DE518.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Message { int size,kind; }; void func_0023C580(void *); void *func_001D2538(struct Message *); void func_001F4E10(void *,void *); void func_001F3BF8(char *p) { struct Message message; void *value; func_0023C580(p); message.size=0x14; message.kind=0x10; value=func_001D2538(&message); *(void **)(p+0x140)=value; func_001F4E10(value,p); }
