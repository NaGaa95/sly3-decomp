// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "gifs.h"
struct CFont {
    unsigned char opaque0[0x3C];
    int testEnabled;
    ulong test;
    unsigned char opaque48[8];
    ulong texture;
};
class CTextBox {public:float x,y,dx,dy;};
struct COORDINATE_CONVERSION_FIELDS;
struct ScreenExtentPrefix {int mode,width,height;};
extern "C" {
extern unsigned char D_0036DBE0[];
float func_002BE228(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE230(COORDINATE_CONVERSION_FIELDS *,float);
int func_00180A88(CFont *,GIFS *);
}
extern "C" void func_00180B60(CFont *font,CTextBox *clip,GIFS *packets)
{
    if(clip) {
        ScreenExtentPrefix *screen=(ScreenExtentPrefix *)D_0036DBE0;
        int x0=(int)func_002BE228((COORDINATE_CONVERSION_FIELDS *)screen,
            clip->x*(float)screen->width*0.0015625f);
        int x1=(int)func_002BE228((COORDINATE_CONVERSION_FIELDS *)screen,
            (clip->x+clip->dx)*(float)screen->width*0.0015625f)-1;
        int y0=(int)func_002BE230((COORDINATE_CONVERSION_FIELDS *)screen,
            clip->y*(float)screen->height*0.0020833334f);
        int y1=(int)func_002BE230((COORDINATE_CONVERSION_FIELDS *)screen,
            (clip->y+clip->dy)*(float)screen->height*0.0020833334f)-1;
        packets->AddPrimPack(0,1,0xE);
        packets->PackAD(0x40,(ulong)x0|((ulong)x1<<16)|((ulong)y0<<32)|((ulong)y1<<48));
    }
    int upload=func_00180A88(font,packets);
    packets->AddPrimPack(6,1,0xE);
    if(upload)
        packets->PackAD(0x3F,0);
    packets->PackAD(0x47,font->testEnabled?font->test:0x31001);
    packets->PackAD(0x42,0x44);
    packets->PackAD(6,font->texture);
    packets->PackAD(0x14,0x60);
    packets->PackAD(8,5);
    packets->PackAD(0,0x1D6);
    packets->AddPrimList(5,0x43431);
}
