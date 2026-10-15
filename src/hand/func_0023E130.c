// Return the first nonzero value from the original nested linked record. Actual receiver and next/value fields are explicit; nominal pointer return type remains provisional until value-producing callers are classified.
// Reference algorithm: src/hand/func_001A9FE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Node {void *value;struct Node *next;};
struct Record {char prefix[0x64];struct Node *head;};
struct S { char unknown_0[0xDC]; struct Record * record; };
void *func_0023E130(struct S *p){struct Node *node;if(p->record){for(node=p->record->head;node;node=node->next)if(node->value)return node->value;}return 0;}
