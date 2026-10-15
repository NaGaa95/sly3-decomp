// Return the original64-byte matrix basis at receiver storage50 plus offset40.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct Matrix4 {
    float rows[4][4];
}
__attribute__((aligned(16)));
struct MatrixStorage {
    char prefix[0x40];
    struct Matrix4 basis;
};
struct Receiver {
    char prefix[0x50];
    const struct MatrixStorage *storage;
};
const struct Matrix4 *func_0023CFB8(const struct Receiver *p) {
    return &p->storage->basis;
}
