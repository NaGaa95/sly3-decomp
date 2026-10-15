// Test both explicit doubly-linked-list inputs, call the adjusted receiver notification, and append the original node only when absent. The receiver-only indirect method signature remains provisional.
// Reference algorithm: src/hand/func_001FB710.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { short delta; short unused; int (*method)(void *); };
extern char D_0047503C[];
struct S { char unknown_0[0xC]; struct V * vtable; };
int func_0011B0C0(void *list,void *node);
void func_0011AF60(void *list,void *node);
void func_00245370(struct S *p){void *list=D_0047503C;if(!func_0011B0C0(list,p)){p->vtable[1].method((char *)p+p->vtable[1].delta);func_0011AF60(list,p);}}
