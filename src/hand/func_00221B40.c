// Clear receiver state and notify the adjusted receiver and attached object through their actual virtual slots; ignored integer returns and receiver-only nominal APIs remain provisional.
// Reference algorithm: src/hand/func_001DD6C8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;int (*method)(void *);};
struct Object {char prefix[0xC];struct V *vtable;};
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x24]; struct Object * object; char unknown_38[0x18]; int state; };
void func_00221B40(struct S *p){p->state=0;if(p->object){p->vtable[11].method((char *)p+p->vtable[11].delta);p->object->vtable[54].method((char *)p->object+p->object->vtable[54].delta);}}
