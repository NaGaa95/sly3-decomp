// Reference algorithm: src/hand/func_001F6838.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
float func_001BBC00(char *p,int index,float a,float b) { if(index != *(int *)(p + 0x6C)) return a + b; return a + b + 1000.0f; }
