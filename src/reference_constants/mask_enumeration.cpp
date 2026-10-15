// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Sly2 func_00207AA0 enumerates47 bits of a64-bit mask; Sly3 enumerates69
// positions from a16-byte mask, descending from68 through0.
// Physical A0 points to the16-byte input; A1 points to32-bit output IDs.
// Snapshot the input before writing any output. The const reference exposes the
// snapshot lifetime across construction of each real temporary bit mask.
// The constructor symbol alias names a genuine external function; it emits no asm.
// D_00475440 is the existing mutable BSS reference mask, never emitted here.
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
extern "C" int func_00252C48(const MaskEnumerationBits *input,int *output) {
    MaskEnumerationBits snapshot=*input;
    const MaskEnumerationBits &value=snapshot;
    int count=0;
    for(int bit=68;bit>=0;--bit) {
        MaskEnumerationBits selected=value&MaskEnumerationBits(bit);
        if(selected!=D_00475440) {
            *output++=bit;
            ++count;
        }
    }
    return count;
}
