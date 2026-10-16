// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct TextCursorPeekWordsView {
    int encoding;unsigned int begin,current,end;
};
extern "C" int func_00181800(void *text,int offset)
{
    const TextCursorPeekWordsView *state=static_cast<TextCursorPeekWordsView *>(text);
    switch(state->encoding) {
    case 0: {
        unsigned int address=state->current+(unsigned int)offset;
        if(address>=state->begin && address<state->end)
            return *reinterpret_cast<const unsigned char *>(address);
        break;
    }
    case 1: {
        unsigned int address=state->current+((unsigned int)offset<<1);
        if(address>=state->begin && address<state->end)
            return *reinterpret_cast<const unsigned short *>(address);
        break;
    }
    }
    return 0;
}
