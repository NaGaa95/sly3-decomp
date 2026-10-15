// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// The original reads all16 inputbytes; only XYZ outputcomponents are scaled.
struct Color3 { float x,y,z; };
struct Color4 { Color3 value; unsigned int opaque_word; } __attribute__((aligned(16)));
extern "C" void func_0011F4E0(Color3 *hsv,Color3 *rgb);
extern "C" void func_0011F6E8(Color4 *input,Color3 *rgb)
{
    Color4 hsv=*input;
    hsv.value.y*=1.0f/255.0f;
    hsv.value.z*=1.0f/255.0f;
    func_0011F4E0(&hsv.value,rgb);
    rgb->x*=255.0f;
    rgb->y*=255.0f;
    rgb->z*=255.0f;
}
