// Reference algorithm: src/hand/func_00184208.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void *func_00197628(void *,int,void *); void *func_00197388(void *p,void *owner,float value) { char *entry = func_00197628(p, 5, owner); *(float *)(entry + 8) = value; return entry; }
