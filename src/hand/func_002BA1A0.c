// Reset the embedded allocator record and invoke the adjusted virtual method on each linked node. The nominal receiver-only indirect method API is provisional; the original callback adjustment and next pointer are explicit.
// Reference algorithm: src/hand/func_001A2028.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *);};
struct Node {int unknown;struct Node *next;struct V *vtable;};
struct S { char unknown_0[0x28]; struct Node * head; };
void func_00118160(void *receiver);
void func_002BA1A0(struct S *p){struct Node *node;func_00118160((char *)p+0x10);for(node=p->head;node;node=node->next)node->vtable[1].method((char *)node+node->vtable[1].delta);}
