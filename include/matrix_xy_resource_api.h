#ifndef SLY3_MATRIX_XY_RESOURCE_API_H
#define SLY3_MATRIX_XY_RESOURCE_API_H
typedef int MatrixXYQuad __attribute__((mode(TI)));
union MatrixXYRow { MatrixXYQuad packed; float value[4]; };
struct MatrixXYSource { union MatrixXYRow row[3]; };
/* Six coefficients; native16-byte alignment makes the whole value32 bytes.
 * Tail padding is ordinary object padding and is not initialized by the conversion. */
struct MatrixXYValue { float value[6]; } __attribute__((aligned(16)));
typedef char CheckMatrixXYSource48[(sizeof(struct MatrixXYSource) == 48) ? 1 : -1];
typedef char CheckMatrixXYValue32[(sizeof(struct MatrixXYValue) == 32) ? 1 : -1];
typedef char CheckMatrixXYValueAlign16[(__alignof__(struct MatrixXYValue) == 16) ? 1 : -1];
void func_00262848(void *receiver, const struct MatrixXYValue *matrix);
#endif
