// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
// Builds a particle batch (positions and velocities from the vertex source), then moves it into world space:
// positions through the owner's matrix, velocities negated.
#include "../P2/mat.h"
#include "../P2/packed_matrix_intrinsics.h"
// Affine transform of a packed point (XYZ through the matrix columns, W through the fourth column).
static inline qword TransformPoint(const MATRIX4 *matrix, qword point)
{
    const qword *columns = (const qword *)matrix;
    qword result;
    asm("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
        : "=j"(result) : "j"(columns[0]), "j"(columns[1]), "j"(columns[2]), "j"(columns[3]), "j"(point));
    return result;
}
struct ParticleBatch {
    int count;
    qword *position, *velocity;
    float *birth, *death;
};
struct AllocationRequest { int bytes, alignment; };
struct VertexMethod { short delta, reserved; void *function; };
struct VertexTable { unsigned char prefix[0x128]; VertexMethod matrixOf; };
struct VertexObject { unsigned char prefix[0xC]; VertexTable *table; };
struct VertexSelf { unsigned char prefix[0x60]; VertexObject *object; };
struct VertexSource { int count; };
extern "C" {
void *func_001D25B0(AllocationRequest *request);
void func_001FF6B0(void *self, ParticleBatch *batch);
void func_001FFC20(void *self, ParticleBatch *batch);
MATRIX4 *func_0011D558(MATRIX4 *out, const MATRIX4 *first, const MATRIX4 *second);
}
static inline void *AllocAligned(int bytes, int alignment)
{
    AllocationRequest request;
    request.bytes = bytes;
    request.alignment = alignment;
    return func_001D25B0(&request);
}
// Scalar argument passed by value: GPR float bits moved into a VU register (QMTC2 keeps the full carrier).
struct ScaleArg {
    qword q;
    ScaleArg(float f)
    {
        qword bits;
        asm("mfc1 %1,%2\n\tqmtc2.ni %1,%0" : "=j"(q), "=&r"(bits) : "f"(f));
    }
};
static inline qword ScaleRow(qword row, ScaleArg s) { return ScalePackedMatrixRow(row, s.q); }
extern "C" ParticleBatch *func_002020C8(VertexSelf *self, VertexSource *source)
{
    ParticleBatch *batch;
    VertexMethod *method;
    MATRIX4 *base;
    int count = source->count;
    int i;
    batch = (ParticleBatch *)AllocAligned(0x14, 16);
    batch->count = count;
    batch->position = (qword *)AllocAligned(count << 4, 16);
    batch->velocity = (qword *)AllocAligned(count << 4, 16);
    batch->birth = 0;
    batch->death = 0;
    func_001FF6B0(self, batch);
    func_001FFC20(self, batch);
    MATRIX4 local, world;
    method = &self->object->table->matrixOf;
    base = (MATRIX4 *)((char *)((void *(*)(void *, MATRIX4 *))method->function)((char *)self->object + method->delta, &local) + 0x40);
    func_0011D558(&world, base, &local);
    for (i = 0; i < count; i++) {
        batch->position[i] = TransformPoint(&world, batch->position[i]);
        qword vel = batch->velocity[i];
        batch->velocity[i] = ScaleRow(vel, ScaleArg(-1.0f));
    }
    return batch;
}
