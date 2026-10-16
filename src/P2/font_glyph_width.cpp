// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct Glyph8 {
    unsigned short character;
    short x, y;
    unsigned short width;
};
struct FontWidthView {
    int opaque0, opaque4, spaceAdvance, opaqueC;
    float scaleX;
};
extern "C" Glyph8 *func_001812B0(void *, unsigned short);
extern "C" float func_00180A30(void *font, int character)
{
    FontWidthView *view=(FontWidthView *)font;
    Glyph8 *glyph=func_001812B0(font, (unsigned short)character);
    if (glyph)
        return (float)(glyph->width+1)*view->scaleX;
    return (float)view->spaceAdvance*view->scaleX;
}
