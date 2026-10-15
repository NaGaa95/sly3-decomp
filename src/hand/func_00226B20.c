// Return the registered object property31 resource when available, otherwise the original shared context resource. Actual helper receiver/property arguments are explicit.
// Reference algorithm: src/hand/func_001ABCE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x28]; void * object; };
extern char D_00475480[];
int func_0013B500(void *object,int property);
void *func_001F4A80(void *object);
void *func_00165B28(void *context);
void *func_00226B20(struct S *p){if(p->object&&func_0013B500(p->object,0x31))return func_001F4A80(p->object);return func_00165B28(D_00475480);}
