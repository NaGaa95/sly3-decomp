// Reference algorithm: src/hand/func_001959C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00261528(void *,int,float,float); void func_001EB300(char *p) { void *object=*(void **)(p+0x16F8); if(object)func_00261528(object,0x3CA,(float)*(int *)(p+0x16E4),(float)*(int *)(p+0x16E8)); }
