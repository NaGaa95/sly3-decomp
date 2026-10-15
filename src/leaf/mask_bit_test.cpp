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
    bool operator!=(const MaskEnumerationBits &other) const {
        for (int j=0;j<16;j++)
            if(bytes[j]!=other.bytes[j])return true;
        return false;
    }
};
extern "C" MaskEnumerationBits D_00475440;
typedef char MaskEnumerationBitsMustBe16[sizeof(MaskEnumerationBits)==16?1:-1];
typedef char MaskEnumerationIDsMustBe4[sizeof(int)==4?1:-1];
extern "C" int func_00253190(const MaskEnumerationBits *input, int index)
{
    MaskEnumerationBits snapshot = *input;
    const MaskEnumerationBits &value = snapshot;
    MaskEnumerationBits selected = value & MaskEnumerationBits(index);
    return selected != D_00475440;
}
