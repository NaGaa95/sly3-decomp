// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct MaskEnumerationBits {
    unsigned char bytes[16];
    MaskEnumerationBits() {}
};
struct MaskOwner { char unknown_0[0x2F4]; MaskEnumerationBits mask; };
extern "C" void func_001F18D0(MaskOwner *owner);
extern "C" void func_00252DE0(MaskOwner *owner,const MaskEnumerationBits *source)
{
    MaskEnumerationBits snapshot=*source;
    owner->mask=snapshot;
    func_001F18D0(owner);
}
