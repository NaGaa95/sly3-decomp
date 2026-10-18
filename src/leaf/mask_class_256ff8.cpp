// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct MaskEnumerationBits {
    unsigned char bytes[16];
    MaskEnumerationBits() {}
    MaskEnumerationBits(int index) asm("func_00252AD0");
    MaskEnumerationBits operator&(const MaskEnumerationBits &other) const {
        MaskEnumerationBits result;
        for (int j=0;j<16;j++)
            result.bytes[j]=bytes[j]&other.bytes[j];
        return result;
    }
    MaskEnumerationBits operator|(const MaskEnumerationBits &other) const {
        MaskEnumerationBits result;
        for (int j=0;j<16;j++)
            result.bytes[j]=bytes[j]|other.bytes[j];
        return result;
    }
    bool operator!=(const MaskEnumerationBits &other) const {
        for (int j=0;j<16;j++)
            if(bytes[j]!=other.bytes[j])return true;
        return false;
    }
};
extern "C" MaskEnumerationBits D_00475440;
typedef char MaskEnumerationBitsMustBe16[sizeof(MaskEnumerationBits)==16?1:-1];
struct Actor { unsigned char prefix[0x2F4]; MaskEnumerationBits mask; };
extern "C" int func_00256FF8(Actor *actor)
{
    return (actor->mask & MaskEnumerationBits(7)) != D_00475440 ? 2 :
           ((actor->mask & (MaskEnumerationBits(5) | MaskEnumerationBits(6))) != D_00475440 ? 1 : 0);
}
