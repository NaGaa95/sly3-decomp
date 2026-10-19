// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "qw.h"

struct PacketResource {
    int identifier;
    unsigned short kind;
    short flags;
    unsigned char channels[4];
    int count;
    const ulong *values;
};
struct ResourcePacket {
    int identifier, count;
    char reserved08[8];
    QW entries[32];
    void *primitiveTemplate;
    int reserved214, channelsScaled;
    unsigned char channels[4];
};
struct PacketContext { char prefix[0x20]; ResourcePacket *packet; };
struct PacketReceiver { char prefix[0x1C]; PacketContext *context; };

extern "C" {
void *func_00235F40(int identifier);
extern char D_0036B2A0[], D_0036B2E0[];
}

extern "C" void func_001FD7E8(void *object)
{
    ResourcePacket *packet = ((PacketReceiver *)object)->context->packet;
    if (packet->primitiveTemplate)
        return;
    const PacketResource *resource = (const PacketResource *)func_00235F40(
        packet->identifier);
    int count = resource->count;
    int remaining = count >> 1;
    uint span = 1;
    while (remaining) {
        remaining >>= 1;
        span <<= 1;
    }
    span <<= ((int)span < count);
    while ((int)span >= 32)
        span = (uint)((int)span >> 1);
    int duplicates = count < (int)span ? (int)(span - (uint)count) : 0;
    packet->count = (int)span;
    QW *entry = packet->entries;
    for (int i = 0; i < count; ++i) {
        entry->aul[0] = resource->values[i];
        entry->aui[2] = 6;
        if (i < duplicates) {
            entry[1] = entry[0];
            ++entry;
        }
        ++entry;
    }
    int flags = resource->flags;
    packet->primitiveTemplate = flags & 1 ? D_0036B2E0 : D_0036B2A0;
    if (!packet->channelsScaled) {
        packet->channelsScaled = 1;
        for (int i = 0; i < 4; ++i)
            packet->channels[i] = (resource->channels[i] + 1) >> 1;
    }
}
