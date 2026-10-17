// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "gifs.h"
struct Glyph8 {unsigned short character,x,y,width;};
struct CFont {
    int opaque0,opaque4,spaceAdvance,lineHeight;
    float scaleX,scaleY;
    unsigned char opaque18[0x48-0x18];
    int depth,opaque4C;
    ulong texture;
};
struct COORDINATE_CONVERSION_FIELDS;
struct ScreenExtentPrefix {int mode,width,height;};
extern "C" {
extern unsigned char D_0036DBE0[];
Glyph8 *func_001812B0(CFont *,unsigned short);
float func_002BE228(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE230(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE248(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE298(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE2E8(COORDINATE_CONVERSION_FIELDS *,float);
float func_002BE2F8(COORDINATE_CONVERSION_FIELDS *,float);
}
extern "C" float func_00180E18(CFont *font,int character,float x,float y,unsigned int color,GIFS *packets)
{
    int textureHeight=1<<(int)((font->texture>>30)&15);
    Glyph8 *glyph=func_001812B0(font,(unsigned short)character);
    if(glyph) {
        float right=x+(float)glyph->width*font->scaleX;
        float bottom=y+(float)font->lineHeight*font->scaleY;
        if(right>=0.0f && x<=640.0f && bottom>=0.0f && y<=480.0f) {
            /* GS alpha is 0..128: (a+1) halved, placed in the top byte. The original computes it as
               ((a+1)&0x1FE)<<23, which is the same value. */
            unsigned int rgba=(color&0xFFFFFF)|((((color>>24)+1)&0x1FE)<<23);
            packets->ListRGBAQ(rgba,0.0f);
            packets->ListUV((int)glyph->x*16,(textureHeight-(int)glyph->y)*16);
            ScreenExtentPrefix *screen=(ScreenExtentPrefix *)D_0036DBE0;
            COORDINATE_CONVERSION_FIELDS *conversion=(COORDINATE_CONVERSION_FIELDS *)screen;
            int x0=(int)func_002BE2E8(conversion,func_002BE248(conversion,
                func_002BE228(conversion,x*(float)screen->width*0.0015625f)));
            int y0=(int)func_002BE2F8(conversion,func_002BE298(conversion,
                func_002BE230(conversion,y*(float)screen->height*0.0020833334f)));
            packets->ListXYZF(x0,y0,font->depth,0);
            packets->ListUV(((int)glyph->x+(int)glyph->width)*16,
                (textureHeight-((int)glyph->y+font->lineHeight))*16);
            int x1=(int)func_002BE2E8(conversion,func_002BE248(conversion,
                func_002BE228(conversion,right*(float)screen->width*0.0015625f)));
            int y1=(int)func_002BE2F8(conversion,func_002BE298(conversion,
                func_002BE230(conversion,bottom*(float)screen->height*0.0020833334f)));
            packets->ListXYZF(x1,y1,font->depth,0);
        }
        return (float)(glyph->width+1)*font->scaleX;
    }
    return (float)font->spaceAdvance*font->scaleX;
}
