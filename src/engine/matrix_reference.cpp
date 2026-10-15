// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
typedef int MatrixReferencePacked __attribute__((mode(TI)));
struct MatrixReferenceRow { float xyz[3]; unsigned int raw_w; } __attribute__((aligned(16)));
struct MatrixReferenceRotation { MatrixReferenceRow rows[3]; };
struct MatrixReferencePosition { float x,y,z,w; } __attribute__((aligned(16)));
struct MatrixReferenceMatrix {
    MatrixReferenceRotation rotation;
    MatrixReferencePosition position;
};
struct MatrixReferenceInput {
    unsigned char prefix[0x30];
    MatrixReferencePacked position;
};
class ScriptMatrixReference {
public:
    CRef value;
    ScriptMatrixReference(int tag) { InitTag(tag); }
    ScriptMatrixReference(const ScriptMatrixReference &other) __asm__("func_0012AF00");
    void InitTag(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~ScriptMatrixReference() { Drop(); }
};
extern "C" void func_0011CCF8(void *input,MatrixReferenceRotation *optional,MatrixReferenceRotation *output);
extern "C" void *func_002BA818(void *output,MatrixReferencePacked value);

extern "C" ScriptMatrixReference func_00124FF0(int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    MatrixReferenceRotation rotation;
    func_0011CCF8(arguments[0].payload.pointer,0,&rotation);
    ScriptMatrixReference result(0x19);
    MatrixReferenceMatrix *matrix = (MatrixReferenceMatrix *)result.value.payload.pointer;
    func_002BA818(&matrix->position,((MatrixReferenceInput *)arguments[0].payload.pointer)->position);
    matrix->rotation = rotation;
    matrix->rotation.rows[2].raw_w = 0;
    matrix->rotation.rows[1].raw_w = 0;
    matrix->rotation.rows[0].raw_w = 0;
    matrix->position.w = 1.0f;
    return result;
}
