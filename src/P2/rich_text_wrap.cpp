// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct RichTextWrapView {
    int encoding;
    void *begin, *current, *end, *currentFont;
};
struct Text;
extern "C" void func_001813B0(char *);
extern "C" float func_00180A30(void *, int);
extern "C" int func_00181800(void *, int);
extern "C" int func_00271928(int character, int next_character);
extern "C" void func_00181888(Text *, unsigned short, int);
extern "C" void func_001818C8(void *, int);
extern "C" int func_00181410(void *);

extern "C" int func_00181910(void *text, float maxWidth)
{
    RichTextWrapView *state=(RichTextWrapView *)text;
    int lines=1;
    float width=0.0f;
    func_001813B0((char *)text);
    int character;
    while((character=func_00181410(text))!=0) {
        if (character==10) {
            width=0.0f;
            ++lines;
        } else {
            width+=func_00180A30(state->currentFont, character);
        }
        if (maxWidth!=0.0f && maxWidth<width) {
            int previous=func_00181800(text, -1);
            int offset=-1;
            while(previous!=0 && previous!=10) {
                int nextOffset=offset+1;
                if (func_00271928(previous, func_00181800(text, nextOffset))) {
                    func_00181888((Text *)text, 10, offset);
                    width=0.0f;
                    ++lines;
                    func_001818C8(text, nextOffset);
                    break;
                }
                --offset;
                previous=func_00181800(text, offset);
            }
            if (width!=0.0f && func_00181800(text, 0)!=0) {
                func_00181888((Text *)text, 10, 0);
                width=0.0f;
                ++lines;
            }
        }
    }
    return lines;
}
