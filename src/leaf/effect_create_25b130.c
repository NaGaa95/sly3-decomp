// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Method { short delta,unused; void (*method)(void *); };
struct Effect { unsigned char prefix[0xC]; struct Method *methods; unsigned char gap10[0x34]; unsigned int flags; unsigned char gap48[8]; float rateA; float rateB; unsigned char gap58[4]; int enabled; };
struct Owner { unsigned char prefix[0x45E4]; struct Effect *effect; };
struct Effect *func_00150690(int kind,int a,int cls,int b);
void func_0025B130(struct Owner *owner)
{
    struct Method *method;
    owner->effect=func_00150690(0x8A,0,0xB,-1);
    owner->effect->rateA=0.1f;
    owner->effect->rateB=0.25f;
    owner->effect->flags=0x80000000;
    owner->effect->enabled=1;
    method=&owner->effect->methods[9];
    method->method((char *)owner->effect+method->delta);
}
