// SLY3_CFLAGS: -Os -G0
// Original vtables independently reference this previously unindexed entry.
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct Matrix { Quadword rows[4]; } Matrix;
typedef struct MatrixObject {
    unsigned char opaque[64];
    void *parent;
    unsigned char opaque2[12];
    Matrix matrix;
} MatrixObject;
extern unsigned char D_0034A160[];

void *func_002901E0(MatrixObject *object, Matrix *output)
{
    if (output) {
        output->rows[0] = object->matrix.rows[0];
        output->rows[1] = object->matrix.rows[1];
        output->rows[2] = object->matrix.rows[2];
        output->rows[3] = object->matrix.rows[3];
    }
    return object->parent ? object->parent : D_0034A160;
}
