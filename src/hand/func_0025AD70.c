// Mark the receiver available and assign the entire opaque 72-byte record.
// Complete original inputs, return and boundaries were independently reviewed.
// The copied record is kept opaque: all 72 original bytes are significant.
// No matrix, pointer, or integer interpretation is inferred for its payload.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int Flags64 __attribute__((mode(DI)));
struct Record72 {
    unsigned char bytes[72];
};
struct Receiver {
    char prefix[0x4344];
    int available;
    struct Record72 record;
};
void func_0025AD70(struct Receiver *receiver,const struct Record72 *input) {
    receiver->available=1;
    receiver->record=*input;
}
