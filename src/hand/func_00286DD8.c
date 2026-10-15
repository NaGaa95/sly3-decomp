// Return the original adjusted virtual predicate or its fallback receiver predicate. Supplied incoming context A1 is forwarded historically but unused by complete1F42E8; its nominal pointer type and receiver-only virtual API remain provisional.
// Reference algorithm: src/hand/func_00226310.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;int (*method)(void *);};
struct S { char unknown_0[0xC]; struct V * vtable; };
int func_001F42E8(void *receiver,int option);
int func_00286DD8(struct S *p,int option){if(p->vtable[81].method((char *)p+p->vtable[81].delta))return 1;return func_001F42E8(p,option);}
