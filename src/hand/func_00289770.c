// Insert the explicit node in the receiver list, store its owner pointer and initialize its reference-dependent fields using both explicit inputs.
// Reference algorithm: src/hand/func_00208208.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Node { char prefix[0xC];void *owner; };
void func_0011AD80(void *list,void *node);
void func_002896D0(void *receiver,void *node);
void func_00289770(void *receiver,struct Node *node){func_0011AD80((char *)receiver+0x678,node);node->owner=receiver;func_002896D0(receiver,node);}
