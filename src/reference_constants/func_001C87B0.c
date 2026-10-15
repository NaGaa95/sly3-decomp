// Complete original address-return leaf, with independently proved entry and ABI.
// The original referenced object is separately owned; it is not emitted by this source.
// SLY3_CFLAGS: -Os -G0
// Return the original shared identity matrix pointer. The virtual receiver is unused.
struct Matrix4 { float elements[16]; } __attribute__((aligned(16)));
extern struct Matrix4 D_003174C0;
struct Matrix4 *func_001C87B0(void *receiver) { return &D_003174C0; }
