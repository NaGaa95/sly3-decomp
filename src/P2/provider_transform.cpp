// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
#include "mat.h"
#include "vector_intrinsics.h"

struct ProviderTransformGame {
    char prefix[0x3EB8];
    int count;
    SCENE_OBJECT *providers[5];
    float weights[5];
};
struct ProviderTransformObject {
    SCENE_OBJECT scene;
    char pad68[0x130 - 0x68];
    int useProviderHeight;
};
typedef char CheckScene68[sizeof(SCENE_OBJECT) == 0x68 ? 1 : -1];
typedef char CheckTransformView138[sizeof(ProviderTransformObject) == 0x138 ? 1 : -1];
typedef char CheckMatrix64[sizeof(MATRIX4) == 64 ? 1 : -1];
extern "C" ProviderTransformGame D_00475480;
extern "C" void *func_002BA818(void *output,qword value);
extern "C" qword func_001C8548(int index);
extern "C" void func_001C8248(SCENE_OBJECT *,qword,MATRIX4 *,float,float);

static inline MATRIX4 *ProviderMatrix(SCENE_OBJECT *object)
{
    SCENE_VIRTUAL_ENTRY *entry = &object->vtable[36];
    return static_cast<MATRIX4 *>(entry->Query(reinterpret_cast<char *>(object) + entry->delta));
}

extern "C" void func_00238D08(ProviderTransformObject *object)
{
    for (int i = 0; i < D_00475480.count; ++i) {
        SCENE_OBJECT *provider = D_00475480.providers[i];
        if (D_00475480.weights[i] != 0.0f) {
            MATRIX4 *current = ProviderMatrix(&object->scene);
            MATRIX4 matrix;
            qword position = *reinterpret_cast<qword *>(&ProviderMatrix(provider)->mat[3]);
            func_002BA818(&matrix.mat[3],position);
            *reinterpret_cast<MATRIX3 *>(&matrix) = *reinterpret_cast<MATRIX3 *>(current);
            matrix.mat[2][3] = 0.0f;
            matrix.mat[1][3] = 0.0f;
            matrix.mat[0][3] = 0.0f;
            matrix.mat[3][3] = 1.0f;
            if (!object->useProviderHeight) {
                matrix.mat[3][2] = PackedVectorZ(*reinterpret_cast<qword *>(&ProviderMatrix(&object->scene)->mat[3]));
            }
            func_001C8248(&object->scene,func_001C8548(i),&matrix,1.0f,1.0f);
        }
    }
}
