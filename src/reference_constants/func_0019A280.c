// Reference algorithm: src/hand/func_001D7780.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Message { int mode,fields[3]; }; void *func_00292034(void *,int,unsigned int); void func_0019A2D0(void *,struct Message *); void func_00238980(void *); void func_0019A280(void *p) { struct Message message; func_00292034(&message,0,sizeof(message)); message.mode=-1; func_0019A2D0(p,&message); func_00238980(p); }
