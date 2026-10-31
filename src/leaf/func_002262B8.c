// Pack the receiver's counted value array into a type-6 reference and return the output.
// SLY3_CFLAGS: -Os -G0
struct Ref;
struct ValuePack {
    char opaque00[0x64];
    int count;
    int values[1];
};
struct Ref *func_0024AEF8(struct Ref *output, int count, int type, void *values);

struct Ref *func_002262B8(struct Ref *output, struct ValuePack *pack)
{
    func_0024AEF8(output, pack->count, 6, pack->values);
    return output;
}
