// SLY3_CFLAGS: -O2 -G0
// The observed matrix occupies four aligned EE quadwords at object offset 80.
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct Matrix { Quadword rows[4]; } Matrix;
typedef struct MatrixObject { unsigned char opaque[80]; Matrix matrix; } MatrixObject;
extern void func_0011D558(Matrix *output, const Matrix *input, const Matrix *current);
extern void func_00290078(MatrixObject *object);

void func_00290228(MatrixObject *object, const Matrix *input)
{
    Matrix temporary;
    func_0011D558(&temporary, input, &object->matrix);
    object->matrix = temporary;
    func_00290078(object);
}
