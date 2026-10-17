// SLY3_CFLAGS: -Os -G0
struct Dim { int w, h; };
extern struct Dim D_0034A098[][4];
unsigned int func_00196A70(unsigned int value);
void func_0027DC08(int width,int height,int *blocks,int *size)
{
    int limitW=0x40,limitH=0x20,unit=8,unitH=8,shift=6;
    int w,h,block,wide,one=1;
    if(width>limitW) {
        if(height>limitH) {
            w=width;
            h=height;
        } else {
            w=width;
            h=limitH;
        }
    } else if(height>limitH) {
        w=limitW;
        h=height;
    } else {
        unsigned int a=func_00196A70(width/unit);
        unsigned int b=func_00196A70(height/unitH);
        w=D_0034A098[b][a].w*8;
        h=D_0034A098[b][a].h*8;
    }
    block=one<<shift;
    wide=width<limitW?limitW:width;
    *blocks=wide/64;
    *size=h*w/block;
}
