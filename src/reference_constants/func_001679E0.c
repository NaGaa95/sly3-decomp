// Reference algorithm: src/hand/func_001A2358.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short displacement; short pad; int (*method)(void *,int); }; struct Object { char pad[12]; struct VTE *vtable; }; int func_001679E0(struct Object *p,int argument,float value) { struct VTE *entry; *(float *)((char *)p + 0x144) = value; entry = p->vtable + 55; return entry->method((char *)p + entry->displacement, argument); }
