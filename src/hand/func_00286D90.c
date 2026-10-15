// Evaluate the explicit object pair and return its original Boolean result, clamping through the scalar minimum helper for the stored matching object.
// Reference algorithm: src/hand/func_001F82B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x204]; void * other; };
int func_0023E178(struct S *p,void *other);
int func_0013CD00(int first,int second);
int func_00286D90(struct S *p,void *other){int result=func_0023E178(p,other);if(other==p->other)result=func_0013CD00(result,1);return result;}
