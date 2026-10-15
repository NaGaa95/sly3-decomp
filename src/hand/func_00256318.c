// Resolve the original resource through the stored object property or its global fallback, explicitly returning the pointer result of the selected helper.
// Reference algorithm: src/hand/func_001709A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
struct S { char unknown_0[0xC]; void * object; };
int func_0013B500(void *object,int property);
void *func_001F4A80(void *object);
void *func_00165B28(void *context);
void *func_00256318(struct S *p){if(!func_0013B500(p->object,0x31))return func_00165B28(D_00475480);return func_001F4A80(p->object);}
