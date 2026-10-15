// Bind the actual receiver to owner A1 and data A2, insert it in the owner list, and snapshot the block generation. Both list helper inputs and all consumed outer pointers are explicit.
// Reference algorithm: src/hand/func_0017D360.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Block {int generation;};
struct Owner {struct Block *block;char unknown[0x28-4];char list[1];};
struct S { struct Block * block; char unknown_4[0x8]; struct Owner * owner; void * data; char unknown_14[0xC]; int generation; };
void func_0011AD80(void *list,void *receiver);
void func_002BA070(struct S *p,struct Owner *owner,void *data){p->block=owner->block;p->data=data;p->owner=owner;func_0011AD80(owner->list,p);p->generation=p->block->generation;}
