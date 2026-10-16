// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ShaderCircleUsers { void *first,*last; int memberOffset; };
struct ShaderCircleView {
    unsigned char beforeUsers[0x38];
    ShaderCircleUsers users;
    unsigned char beforeSpeed[0x50-0x44];
    float speed,radius,uCenter,vCenter;
};
struct ShaderCircleClock { float current,delta; };
struct ShaderScrollCycle;
extern "C" ShaderCircleClock D_0036BB98;
extern "C" int func_0011AEF8(void *);
extern "C" float func_0011E3B8(float);
extern "C" void func_0011EB28(float *,float *,float);
extern "C" void func_00237298(ShaderScrollCycle *,float,float);
extern "C" void func_00237E38(ShaderCircleView *circle)
{
    if (func_0011AEF8(&circle->users)) return;
    float angle=func_0011E3B8(D_0036BB98.current*circle->speed);
    float sine,cosine;
    func_0011EB28(&sine,&cosine,angle);
    sine=sine*circle->radius+circle->uCenter;
    cosine=cosine*circle->radius+circle->vCenter;
    func_00237298((ShaderScrollCycle *)circle,sine,cosine);
}
