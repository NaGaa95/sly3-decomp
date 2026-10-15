// Reference algorithm: src/hand/func_00144338.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0013BD00(void *,void *); int func_0013B500(void *,int); void func_00149E08(char *p,char *object) { func_0013BD00(p,object); if(func_0013B500(object,0x1B)) { *(void **)(p+0xD0)=object; *(float *)(p+0x34)=*(float *)(object+0x34); } }
