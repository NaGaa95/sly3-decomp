// Reset each original linked-node receiver and destroy the address-only temporary with flags2. Complete2BE948 consumes flags only on this path and never reads temporary storage; the nominal temporary class and outer return API remain provisional.
// Reference algorithm: src/hand/func_00156D98.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Node {char prefix[0x24];struct Node *next;};
struct S { char unknown_0[0x6C]; struct Node * head; };
void func_001FF4C0(void *receiver);
void func_002BE948(void *receiver,int flags);
void func_00203030(struct S *p){QWORD unused_temporary;struct Node *node;for(node=p->head;node;node=node->next)func_001FF4C0(node);func_002BE948(&unused_temporary,2);}
