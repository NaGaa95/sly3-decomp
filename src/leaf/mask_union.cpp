// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Shared access view is byte-identical to the current enumeration declaration.
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
extern "C" MaskEnumerationBits func_00252B60(int count, const int *indices)
{
    MaskEnumerationBits result = D_00475440;
    for (int i = 0; i < count; ++i) {
        MaskEnumerationBits selected(indices[i]);
        for (int j = 0; j < 16; ++j)
            result.bytes[j] |= selected.bytes[j];
    }
    return result;
}
