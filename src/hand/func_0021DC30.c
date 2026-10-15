// Find the explicit identifier in the original linked chain; the absent sentinel returns the current head without traversing.
// Reference algorithm: src/hand/func_001F83E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Node { char prefix[0x10];struct Node *next;char unknown[4];int id; };
struct S { struct Node *head; };
struct Node *func_0021DC30(struct S *p,int id){struct Node *node=p->head;while(node && id!=-1 && node->id!=id)node=node->next;return node;}
