// Reference algorithm: src/hand/func_001C3DC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_00139A40(void *); void func_00139A98(char *p,void *key) { *(int *)(p + 0x40) = func_00139A40(key); }
