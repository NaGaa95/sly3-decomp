// Complete original Sly3 body; ordinary source/profile reconstruction.
// A0 holds two word slots at0x10; unsigned A1 bounds the lookup to0 or1, otherwise returning -1.
// SLY3_CFLAGS: -Os -G0
struct Object { char pad[0x10]; int values[2]; }; int func_00185700(struct Object *p,unsigned int index) { return index<2?p->values[index]:-1; }
