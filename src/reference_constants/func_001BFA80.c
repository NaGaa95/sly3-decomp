// Reference algorithm: src/hand/func_001B0808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C0DA8(void *,void *,float); void func_001BFA80(char *p) { char *context=*(char **)(p+0xC); if(!*(int *)(context+0x18C))func_001C0DA8(*(char **)p+0xA20,context?context+0x180:0,*(float *)(p+0x10)); }
