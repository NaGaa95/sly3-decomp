// Reference algorithm: src/hand/func_00151648.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001B40F0(void *,int,void *,void *); void func_00154EF0(char *p,void *handle,void *context,void *value) { if(!handle)handle=*(void **)(p+0xA08); *(void **)(p+0xA0C)=handle; func_001B40F0(p+0x500,0xC,context,0); *(void **)(p+0x1404)=value; }
