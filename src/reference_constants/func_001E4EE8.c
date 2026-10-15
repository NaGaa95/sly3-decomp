// Reference algorithm: src/hand/func_001C0320.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001E4FC8(void *,int,void *); void func_001E5070(void *,void *,int); int func_001E4EE8(void *p,char *source) { if(!func_001E4FC8(p, *(int *)(source + 0x50), *(void **)(source + 0x14))) return 0; func_001E5070(p, *(void **)(source + 0x14), *(int *)(source + 0x20)); return 1; }
