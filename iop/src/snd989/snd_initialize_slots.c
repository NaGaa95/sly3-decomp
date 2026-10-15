/* Module07 E490/76: initialize generic sound-handler slot headers. */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct SndInitialSlotView {
    u32 handle;
    void *occupied;
    void *object08;
    u8 opaque0c[10];
    u8 flags16;
    u8 flags17;
    void *link18;
    void *link1c;
} SndInitialSlotView;

void snd_initialize_slots(SndInitialSlotView *slot, int count, u32 kind, u32 stride)
{
    int index = 0;
    if (count <= 0)
        return;
    kind <<= 24;
    do {
        slot->handle = ((u32)index << 16) | kind | 1;
        slot->occupied = 0;
        slot->object08 = 0;
        slot->flags16 = 0;
        slot->flags17 = 0;
        slot->link1c = 0;
        slot->link18 = 0;
        slot = (SndInitialSlotView *)((u8 *)slot + stride);
        ++index;
    } while (index < count);
}
