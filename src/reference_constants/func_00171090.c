// Reference algorithm: src/hand/func_00173A18.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Entry { int key; void *value; }; extern struct Entry D_003210E0[]; void func_00239FE0(void *,void *); void func_00170F60(void *,int); void func_00171090(char *p) { int index=*(int *)(p+0x140); *(int *)(p+0x144)=index; func_00239FE0(*(void **)(p+0x13C),D_003210E0[index].value); func_00170F60(p,3); }
