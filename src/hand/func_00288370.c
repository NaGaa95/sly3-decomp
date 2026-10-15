// Construct the inherited record with actual owner A1/tag A2, store explicit object A3 and install its original vtable and derived kind;169C90 stores both supplied base inputs and returns receiver.
// Reference algorithm: src/hand/func_00151648.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -O2 -G0 -fno-schedule-insns
extern char D_0036A850[];
struct S { char unknown_0[0x8]; int kind; char unknown_C[0x10]; void * vtable; char unknown_20[0x8]; void * object; };
struct S *func_00169C90(struct S *receiver,void *owner,int tag);
static inline void Init(struct S *p,void *object){p->object=object;p->vtable=D_0036A850;p->kind=12;}
struct S *func_00288370(struct S *p,void *owner,int tag,void *object){func_00169C90(p,owner,tag);Init(p,object);return p;}
