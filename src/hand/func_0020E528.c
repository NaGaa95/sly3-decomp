// Reset and invoke the adjusted release callback of the attached receiver, clear its pointer, then perform inherited cleanup. Nominal receiver-only indirect callback API is provisional; direct helper inputs are explicit.
// Reference algorithm: src/hand/func_002108E8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *);};
struct Object {char prefix[0xC];struct V *vtable;};
struct S { char unknown_0[0xF8]; struct Object * object; };
void func_00203030(void *receiver);
void func_0020BD70(void *receiver);
void func_0020E528(struct S *p){if(p->object){func_00203030(p->object);p->object->vtable[2].method((char *)p->object+p->object->vtable[2].delta);p->object=0;}func_0020BD70(p);}
