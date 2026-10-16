// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct RichTextInitView {
    int encoding;
    unsigned short *begin, *current, *end;
    void *currentFont, *baseFont;
    unsigned char opaque[0x160-0x18];
    int dirty;
    unsigned int colorCurrent, colorSet, colorBase, colorOther;
};
extern "C" int func_00271700(const unsigned short *);
extern "C" void func_001813B0(char *);
extern "C" void *func_00181330(void *output, void *text, void *font)
{
    RichTextInitView *state=(RichTextInitView *)output;
    state->encoding=1;
    state->begin=(unsigned short *)text;
    state->end=state->begin+func_00271700((unsigned short *)text)+1;
    state->baseFont=font;
    state->colorOther=0xFF808080;
    state->colorBase=0xFF808080;
    state->colorSet=0xFF808080;
    state->colorCurrent=0xFF808080;
    func_001813B0((char *)state);
    return output;
}
