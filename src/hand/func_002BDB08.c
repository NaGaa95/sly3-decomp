// Return the word at offset 0x1C from the read-only record selected by the owner.
// Reference algorithm: src/hand/func_00130488.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char pad[0x1C]; int value; };
struct R *func_002BD7E8(void *owner, int mutable);
int func_002BDB08(void *owner)
{
    return func_002BD7E8(owner, 0)->value;
}
