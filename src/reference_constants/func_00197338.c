// Reference algorithm: src/hand/func_00184208.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Record { int kind; void *value; void *extra; }; struct Record *func_00197628(void *,int,void *); void func_00197338(void *p,void *value,void *extra) { func_00197628(p, 3, value)->extra = extra; }
