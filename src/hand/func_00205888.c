// Return the original ordered comparison of the virtual result scalar against one-half. Adjusted virtual receiver is explicit; the nominal receiver-only indirect return-record API remains provisional.
// Reference algorithm: src/hand/func_00162670.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Result {char prefix[0x28];float value;};
struct V {short delta;short unused;struct Result *(*method)(void *);};
struct S {char prefix[0xC];struct V *vtable;};
int func_00205888(struct S *p){return p->vtable[36].method((char *)p+p->vtable[36].delta)->value>0.5f;}
