// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/vifs.h"
#include "../P2/gifs.h"

struct FrameColor { uchar r, g, b, a; };
extern FrameColor D_0036BC44;
extern unsigned char D_0036E680[];
extern "C" {
void *func_00168968(unsigned int flags);
void func_00196F28(void *self, void *table, QW *output);
void func_00195808(FrameColor *color, QW *quad, int flags, GIFS *gifs);
}
extern "C" void func_001689A8(char *self, int flags, VIFS *vifs)
{
    vifs->AddDmaCall((QW *)func_00168968(flags));
    QW state[64];
    GIFS gifs;
    QW quad;
    FrameColor color;
    gifs.AllocStatic(64, state);
    func_00196F28(self + 0x160, D_0036E680, &quad);
    color = D_0036BC44;
    func_00195808(&color, &quad, flags, &gifs);
    vifs->AddDmaCnt();
    vifs->AddVifDirect((uint)(gifs.m_pb - gifs.m_ab) >> 4, (QW *)gifs.m_ab, 0);
    if(flags & 8) vifs->AddVifBaseOffset(0x34, 0x1E6);
    vifs->EndDmaCnt();
}
