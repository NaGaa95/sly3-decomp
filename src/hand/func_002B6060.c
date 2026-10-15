// Construct the inherited and embedded receivers and install both original interface tables.
// Reference algorithm: src/hand/func_0012F8F0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00354B88[],D_00354BC8[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x20C]; void * interface; };
struct S *func_002B56A0(struct S *p);
void *func_002B8848(void *p);
struct S *func_002B6060(struct S *p){func_002B56A0(p);func_002B8848((char *)p+0x130);p->interface=D_00354B88;p->vtable=D_00354BC8;return p;}
