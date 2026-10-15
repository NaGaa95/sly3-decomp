// Forward actual owner A1 and descriptor A2 through the inherited constructor, initialize its derived list/table and apply both original receiver updates, returning receiver.1FEEF8 stores/uses both actual pointers.
// Reference algorithm: src/hand/func_001256E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003615B8[];
struct S { char unknown_0[0x40]; void * vtable; };
struct S *func_001FEEF8(struct S *receiver,void *owner,void *descriptor);
void func_0011AF38(void *list,int next_offset);
void func_002008C0(void *receiver,int option);
void func_001FF4D8(void *receiver);
struct S *func_00200868(struct S *p,void *owner,void *descriptor){func_001FEEF8(p,owner,descriptor);p->vtable=D_003615B8;func_0011AF38((char *)p+0x50,0x1090);func_002008C0(p,0);func_001FF4D8(p);return p;}
