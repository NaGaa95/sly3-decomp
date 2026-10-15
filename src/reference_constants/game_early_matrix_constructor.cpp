// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Construct a matrix reference by retaining a new pool-backed matrix copy.
typedef int MatrixQuad __attribute__((mode(TI)));
struct MatrixRows {
    MatrixQuad row[4];
};
struct MatrixBuffer {
    MatrixRows matrix;
    int references;
};
struct MatrixCRef {
    short tag;
    unsigned short word2;
    union { void *pointer; MatrixBuffer *matrix; } payload;
};
typedef char CheckMatrix64[(sizeof(MatrixRows) == 64) ? 1 : -1];
typedef char CheckMatrixBuffer80[(sizeof(MatrixBuffer) == 80) ? 1 : -1];
typedef char CheckMatrixCRef8[(sizeof(MatrixCRef) == 8) ? 1 : -1];
typedef char CheckMatrixRowAlign16[(__alignof__(MatrixQuad) == 16) ? 1 : -1];
extern char D_004D2F40[];
extern "C" void *func_0011E118(void *pool);
extern "C" MatrixCRef *func_0012B008(MatrixCRef *output, const MatrixRows *matrix)
{
    output->tag = 0x19;
    MatrixBuffer *buffer = (MatrixBuffer *)func_0011E118(D_004D2F40);
    buffer->references = 0;
    output->payload.matrix = buffer;
    ++buffer->references;
    output->payload.matrix->matrix = *matrix;
    return output;
}
