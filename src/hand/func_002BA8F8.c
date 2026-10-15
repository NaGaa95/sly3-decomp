// Decrement the actual unsigned16 reference counter and release its receiver only on wrap-to-zero, then perform the original local deletion flag check. Both cleanup flag arguments and historically supplied unused1D2818 object are explicit.
// Reference compiler shape: src/hand/func_0017F8C8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Object {unsigned short unknown;short references;};
struct Ref {struct Object *object;};
void func_002BA840(void *receiver,int flags);
void func_001D2818(void *receiver);
void func_002BA8F8(struct Ref *p,int flags){struct Object *object=p->object;if(object&&--object->references==0)func_002BA840(object,3);if(flags&1)func_001D2818(p);}
