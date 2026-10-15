// Reference algorithm: src/hand/func_00149398.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00152488(void *,void *); void func_00258958(void *); void func_00155190(void *,int); void *func_0023DDA0(void *,int,int); void func_001E9478(char *p,void *stream) { func_00152488(p,stream); func_00258958(p+0x1480); func_00258958(p+0x1530); func_00258958(p+0x15E0); func_00155190(p,0x2E); *(void **)(p+0x1190)=func_0023DDA0(p,0x22,1); }
