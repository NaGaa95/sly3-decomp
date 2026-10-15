// Allocate and store the original0x70-byte record of kind0x10 when explicitly requested.
// Reference algorithm: src/hand/func_00149358.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Message { int size;int kind; };
struct S { char unknown_0[0x120]; void * record; };
void *func_001D2538(struct Message *message);
void func_00241678(struct S *object,int allocate)
{
    if(allocate){struct Message message;message.size=0x70;message.kind=0x10;object->record=func_001D2538(&message);}
}
