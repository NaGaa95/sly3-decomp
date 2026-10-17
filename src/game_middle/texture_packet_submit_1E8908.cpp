// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"
#include "../P2/vifs.h"

struct TextureRect { int left, top, right, bottom; };
struct TextureSource {
    unsigned char opaque00[0x160];
    TextureRect rect;
    unsigned char opaque170[0x454 - 0x170];
    int lowBits;
    unsigned char opaque458[0x460 - 0x458];
    int midBits;
};
extern "C" int func_00196A70(int value);

extern "C" void func_001E8908(TextureSource *source, VIFS *vifs)
{
    GIFS packets;
    QW storage[4];
    TextureRect *rect = &source->rect;
    int width, height;
    long tex;
    packets.AllocStatic(4, storage);
    packets.AddPrimPack(0, 1, 0xE);
    width = func_00196A70(rect->right - rect->left);
    height = func_00196A70(rect->bottom - rect->top);
    tex = source->lowBits | ((long)source->midBits << 14) | ((long)width << 26) | ((long)height << 30) | (1L << 34);
    packets.PackAD(6, tex);
    packets.PackAD(0x14, 0x60);
    packets.PackAD(8, 5);
    packets.AddPrimEnd();
    vifs->AddVifDirect((unsigned int)(packets.m_pb - packets.m_ab) >> 4, (QW *)packets.m_ab, 0);
}
