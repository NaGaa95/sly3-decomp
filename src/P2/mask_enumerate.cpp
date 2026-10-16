// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct MaskEnumerationBits {
    unsigned char bytes[16];
    MaskEnumerationBits() {}
};
struct MaskOwner { char unknown_0[0x2F4]; MaskEnumerationBits mask; };
extern "C" int func_00252C48(const MaskEnumerationBits *input,int *output);
extern "C" void func_0024AEF8(void *receiver,int count,int tag,const int *values);
extern "C" MaskOwner *func_00253400(MaskOwner *receiver,const MaskOwner *source)
{
    int ids[72];
    MaskEnumerationBits mask=source->mask;
    int count=func_00252C48(&mask,ids);
    func_0024AEF8(receiver,count,0x100F,ids);
    return receiver;
}
