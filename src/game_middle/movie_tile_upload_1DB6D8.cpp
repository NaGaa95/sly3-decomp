// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"

struct TileScreenView {
    void *vtable;
    int width, height;
    unsigned char opaque0C[0x1C - 0xC];
    int texture_page;
};
struct TileRenderState {
    unsigned char opaque00[0x110];
    unsigned char *packet_buffer;
    int opaque114;
    int width, height;
};

extern "C" {
extern unsigned char D_0036DBE0[];
}

extern "C" void func_001DB6D8(TileRenderState *state)
{
    unsigned char *source = state->packet_buffer + 0x285A80;
    int blocks_x = state->width / 16;
    int blocks_y = state->height / 16;
    GIFS packets;
    packets.AllocStatic(0x22D6, (QW *)(state->packet_buffer + 0x3F8E80));
    packets.AddDmaCnt();
    packets.AddPrimPack(0, 1, 0xE);
    TileScreenView *screen = (TileScreenView *)D_0036DBE0;
    packets.PackAD(0x50, ((long)(screen->texture_page * 3) << 32) | 0xC000000000000L);
    packets.PackAD(0x52, 0x1000000010L);
    for (int x = 0; x < blocks_x; x++) {
        for (int y = 0; y < blocks_y; y++) {
            int column = x * 16;
            int row = y * 16;
            packets.AddPrimPack(0, 1, 0xE);
            packets.PackAD(0x51, ((long)column << 32) | ((long)row << 48));
            packets.PackAD(0x53, 0);
            packets.AddImage(0x40);
            packets.AddDmaRefs(0x40, (QW *)((unsigned int)source & 0xFFFFFFF));
            source += 0x400;
        }
    }
    packets.AddPrimPack(0, 1, 0xE);
    packets.PackAD(0x3F, 0);
    packets.PackAD(0x61, 0);
    packets.AddPrimEnd();
    packets.AddDmaEnd();
    packets.Detach(0, 0);
}
