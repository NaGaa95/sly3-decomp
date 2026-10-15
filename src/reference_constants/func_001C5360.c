// Reference algorithm: src/hand/func_001D4F50.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C81B8(void *); void func_001C5868(void *); void func_001C5360(char *p) { int limit; char *owner; func_001C81B8(p); limit = 0; owner = *(char **)(p + 0x40); if(owner) limit = *(int *)(owner + 0xA4); if(*(int *)(p + 0xD4) < limit) { *(int *)(p + 0xD4) = limit; func_001C5868(p); } }
