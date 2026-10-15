// Reference algorithm: src/hand/func_001EE420.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0014C0B8(void *,int,void *); void func_0014CE20(void *); void func_001D6E78(char *p,int event,void *owner) { func_0014C0B8(p, event, owner); if(event == 1 && *(void **)(p + 0x1F0) == owner) func_0014CE20(p); }
