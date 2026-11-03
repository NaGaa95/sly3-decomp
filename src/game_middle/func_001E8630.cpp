// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/vifs.h"
#include "../P2/gifs.h"

struct ClearRectFrame {
    ulong FBP : 9;
    ulong pad9 : 7;
    ulong FBW : 6;
    ulong pad22 : 2;
    ulong PSM : 6;
    ulong pad30 : 2;
    ulong FBMSK : 32;
};
struct ClearRect {
    int left, top, right, bottom;
    int Width() const { return right - left; }
    int Height() const { return bottom - top; }
};
struct ClearRectScreen {
    unsigned char opaque00[0x160];
    ClearRect rect;
    unsigned char opaque170[0x450 - 0x170];
    unsigned char color[4];
    int frame_address;
    int depth_address;
};

extern "C" void *func_00292034(void *destination, int byte, unsigned int bytes);

extern "C" void func_001E8630(ClearRectScreen *screen, int fill, VIFS *vifs)
{
    QW buffer[0x40];
    GIFS packets;
    ClearRectFrame frame;
    packets.AllocStatic(0x40, buffer);
    int frame_base = screen->frame_address >> 5;
    int depth_base = screen->depth_address >> 5;
    func_00292034(&frame, 0, 8);
    frame.FBP = frame_base;
    int width = 0x40;
    int raw = screen->rect.Width();
    if (raw > width) width = raw;
    frame.FBW = width / 64;
    frame.PSM = 0;
    packets.AddPrimPack(0, 1, 0xE);
    packets.PackAD(0x4C, *(long *)&frame);
    packets.PackAD(0x4E, depth_base | 0x30000000);
    int half_width = screen->rect.Width() / 2;
    int half_height = screen->rect.Height() / 2;
    int offset_y = 0x800 - half_height;
    int offset_x = 0x800 - half_width;
    int scaled_y = offset_y << 4;
    packets.PackAD(0x18, ((long)scaled_y << 32) | (offset_x << 4));
    packets.PackAD(0x40, ((long)(screen->rect.Width() - 1) << 16) | ((long)(screen->rect.Height() - 1) << 48));
    if (fill) {
        packets.PackAD(0x47, 0x30000);
        packets.PackAD(1, ((ulong)screen->color[0] | ((ulong)screen->color[1] << 8) | ((ulong)screen->color[2] << 16) | ((ulong)screen->color[3] << 24)) | 0x100000000L);
        packets.AddPrimPack(6, 1, 5);
        int limit_x = 0x1000 - offset_x;
        int limit_y = 0x1000 - offset_y;
        int x = offset_x & -0x20;
        while (x < limit_x) {
            packets.PackXYZ(x << 4, scaled_y, 0);
            x += 0x20;
            packets.PackXYZ(x << 4, limit_y << 4, 0);
        }
    }
    packets.AddPrimEnd();
    vifs->AddDmaCnt();
    vifs->AddVifFlusha();
    vifs->AddVifDirect(((uint)packets.m_pb - (uint)packets.m_ab) >> 4, (QW *)packets.m_ab, 0);
    vifs->EndDmaCnt();
}
