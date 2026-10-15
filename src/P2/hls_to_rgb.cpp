// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Hue, lightness, saturation to RGB; all source components load before stores.
struct Color3 { float x,y,z; };
extern "C" float func_0011F970(float lower,float upper,float degrees);
extern "C" void func_0011FA88(Color3 *hls,Color3 *rgb)
{
    float saturation=hls->z;
    float lightness=hls->y;
    if (saturation==0.0f) {
        rgb->x=lightness;
        rgb->y=lightness;
        rgb->z=lightness;
        return;
    }
    float hue=hls->x;
    float upper;
    if (lightness<=0.5f)
        upper=lightness+lightness*saturation;
    else
        upper=lightness+saturation-lightness*saturation;
    float lower=lightness*2.0f-upper;
    rgb->x=func_0011F970(lower,upper,hue+120.0f);
    rgb->y=func_0011F970(lower,upper,hue);
    rgb->z=func_0011F970(lower,upper,hue-120.0f);
}
