// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct ColorSetterRGBA { unsigned char red, green, blue, alpha; };
struct ColorSetterOwner { unsigned char prefix[0x20]; ColorSetterRGBA color; };
extern "C" void func_00236908(ColorSetterRGBA *color);

extern "C" void func_001691B0(ColorSetterOwner *owner, const ColorSetterRGBA *source)
{
    owner->color = *source;
    func_00236908(&owner->color);
}
