// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
struct PackedColor {
    unsigned char r,g,b,a;
} __attribute__((packed));
struct Font140 {
    int opaque0,opaque4,spaceAdvance,lineHeight;
    float scaleX,scaleY;
    unsigned char opaque18[0x140-0x18];
} __attribute__((aligned(16)));
struct RichTextNextView {
    int encoding;
    void *begin,*current,*end;
    Font140 *currentFont,*baseFont;
    unsigned char opaque18[8];
    Font140 otherFont;
    int dirty;
    PackedColor colorCurrent,colorSet,colorBase,colorOther;
};
extern "C" int func_00181800(void *,int);
extern "C" void func_001818C8(void *,int);
extern "C" Font140 *func_00180898(int);
extern "C" void func_00180980(void *,float,float);
extern "C" void func_001809E0(void *);

extern "C" int func_00181410(RichTextNextView *state)
{
    int done=0;
    do {
        int character=func_00181800(state,0);
        switch(character) {
        case '~':
            if(func_00181800(state,1)==character) {
                func_001818C8(state,1);
                done=1;
            } else if(func_00181800(state,1)=='.') {
                state->colorSet=state->colorBase;
                state->colorCurrent=state->colorSet;
                func_001818C8(state,2);
            } else {
                int next=func_00181800(state,1);
                unsigned int rgb=0;
                int offset=1;
                while(next!=0 && offset<7) {
                    int digit;
                    if((unsigned short)(next-'0')<10)
                        digit=next-'0';
                    else if((unsigned short)(next-'A')<6)
                        digit=next-'A'+10;
                    else if((unsigned short)(next-'a')<6)
                        digit=next-'a'+10;
                    else
                        break;
                    rgb=(rgb<<4)+digit;
                    ++offset;
                    next=func_00181800(state,offset);
                }
                if(offset>=7) {
                    state->colorSet.r=(((rgb>>16)&255)+1)>>1;
                    state->colorSet.g=(((rgb&0xFF00)>>8)+1)>>1;
                    state->colorSet.b=((rgb&255)+1)>>1;
                    state->colorCurrent=state->colorSet;
                    func_001818C8(state,offset);
                } else {
                    state->currentFont=state->baseFont;
                    state->colorCurrent=state->colorBase;
                    done=1;
                }
            }
            break;
        case '&':
            if(func_00181800(state,1)==character) {
                func_001818C8(state,1);
                done=1;
            } else if(func_00181800(state,1)=='.') {
                state->currentFont=state->baseFont;
                state->colorCurrent=state->colorSet;
                state->dirty=1;
                func_001818C8(state,2);
            } else {
                Font140 *font=func_00180898(func_00181800(state,1));
                if(font) {
                    Font140 *other=&state->otherFont;
                    *other=*font;
                    func_001818C8(state,2);
                    float factor=((float)state->baseFont->lineHeight*state->baseFont->scaleY)/
                                 ((float)other->lineHeight*other->scaleY);
                    state->currentFont=other;
                    state->otherFont.scaleX*=factor;
                    state->otherFont.scaleY*=factor;
                    unsigned char alpha=state->colorCurrent.a;
                    PackedColor color=state->colorOther;
                    color.a=alpha;
                    state->colorCurrent=color;
                } else {
                    state->currentFont=state->baseFont;
                    state->colorCurrent=state->colorBase;
                    done=1;
                }
                state->dirty=1;
            }
            break;
        case '^':
            if(func_00181800(state,1)==character) {
                func_001818C8(state,1);
                done=1;
            } else if(func_00181800(state,1)=='.') {
                func_001809E0(state->currentFont);
                func_001818C8(state,2);
            } else {
                int first=func_00181800(state,1);
                int second=func_00181800(state,2);
                float factor=(float)(first-'0')+(float)(second-'0')*0.1f;
                func_00180980(state->currentFont,
                    factor*state->currentFont->scaleX,
                    factor*state->currentFont->scaleY);
                func_001818C8(state,3);
            }
            break;
        default:
            done=1;
            break;
        }
    } while(!done);
    func_001818C8(state,1);
    return func_00181800(state,-1);
}
