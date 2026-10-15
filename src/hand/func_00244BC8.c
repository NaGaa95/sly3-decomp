// Construct the original base, bind its concrete vtable and initialize the four scalar defaults.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0xC];const void *vtable;float first;char gap[0x1C];float second,third;char gap2[0x10];float fourth;};
extern const char D_00365D50[];void *func_002B8670(void *receiver);
struct S *func_00244BC8(struct S *p){func_002B8670(p);p->vtable=D_00365D50;p->first=1.0f;p->fourth=1.0f;p->second=300.0f;p->third=3000.0f;return p;}
