// Append the original encoded command word and advance the packet cursor.
// Reference algorithm: src/hand/func_0014FCC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char prefix[0xC]; unsigned int *cursor; };
void func_0027E388(struct S *packet,unsigned int value)
{
    unsigned int *cursor=packet->cursor;
    packet->cursor=cursor+1;
    *cursor=value|0x05000000u;
}
