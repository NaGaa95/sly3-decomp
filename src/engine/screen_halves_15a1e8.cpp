// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"
struct ScreenConv { void *vtable; int widthSelector; int heightSelector; int unknownC; int divisor; unsigned char gap14[0x30 - 0x14]; long field30; unsigned char gap38[8]; long field40; };
extern "C" {
int func_002BC640(ScreenConv *, int);
int func_002BC648(ScreenConv *, int);
int func_002BC668(ScreenConv *, int);
int func_002BC670(ScreenConv *, int);
}
extern GIFS D_0036C2E0;
extern ScreenConv D_0036DBE0;
extern QW D_0036E630[2];
extern QW D_0036E650[2];
static inline int ScreenX(ScreenConv *c, int v) { int offset = 2048 - func_002BC640(c, c->widthSelector) / 2; return func_002BC668(c, v + offset); }
static inline int ScreenY(ScreenConv *c, int v) { int offset = 2048 - func_002BC648(c, c->heightSelector) / 2; return func_002BC670(c, v + offset); }

extern "C" void func_0015A1E8()
{
    GIFS *g = &D_0036C2E0;
    g->AddPrimPack(0, 1, 0xE);
    g->PackAD(0x4D, (D_0036DBE0.field40 & 0x1FF) | (D_0036DBE0.field30 & 0x3F0000));
    g->PackAD(0x48, 0x31001);
    g->EndDmaCnt();
    g->AddDmaRefs(2, D_0036E630);
    g->AddDmaCnt();
    g->AddPrimPack(0x316, 7, 0x053531EEL);
    g->PackAD(0x15, 0x61);
    g->PackAD(0x3F, 0);
    g->PackRGBA(0x80808080);
    g->PackUV(8, 8);
    g->PackXYZ(ScreenX(&D_0036DBE0, 0), ScreenY(&D_0036DBE0, 0), 0);
    g->PackUV(func_002BC640(&D_0036DBE0, D_0036DBE0.widthSelector) * 16 + 8, func_002BC648(&D_0036DBE0, D_0036DBE0.heightSelector) * 16 | 8);
    g->PackXYZ(ScreenX(&D_0036DBE0, func_002BC640(&D_0036DBE0, D_0036DBE0.widthSelector) / 2), ScreenY(&D_0036DBE0, func_002BC648(&D_0036DBE0, D_0036DBE0.heightSelector)), 0);
    g->EndDmaCnt();
    g->AddDmaRefs(2, D_0036E650);
    g->AddDmaCnt();
    g->AddPrimPack(0x316, 7, 0x053531EEL);
    g->PackAD(0x15, 0x61);
    g->PackAD(0x3F, 0);
    g->PackRGBA(0x80808080);
    g->PackUV(8, 8);
    g->PackXYZ(ScreenX(&D_0036DBE0, func_002BC640(&D_0036DBE0, D_0036DBE0.widthSelector) / 2), ScreenY(&D_0036DBE0, 0), 0);
    g->PackUV(func_002BC640(&D_0036DBE0, D_0036DBE0.widthSelector) * 16 + 8, func_002BC648(&D_0036DBE0, D_0036DBE0.heightSelector) * 16 | 8);
    g->PackXYZ(ScreenX(&D_0036DBE0, func_002BC640(&D_0036DBE0, D_0036DBE0.widthSelector)), ScreenY(&D_0036DBE0, func_002BC648(&D_0036DBE0, D_0036DBE0.heightSelector)), 0);
}
