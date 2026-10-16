// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct TextCursorView {
    int encoding;
    unsigned int begin, current, end;
};
extern "C" void func_001818C8(void *text, int count)
{
    TextCursorView *view=(TextCursorView *)text;
    switch (view->encoding) {
        case 0:view->current+=(unsigned int)count; return;
        case 1:view->current+=(unsigned int)count<<1; return;
    }
}
