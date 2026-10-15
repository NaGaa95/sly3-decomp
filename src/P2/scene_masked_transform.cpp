// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "mat.h"

struct SceneLightingPayload;
struct SceneMaskedTransform {
    char prefix[0x2C];
    unsigned char mask;
    char pad2D[0x104 - 0x2D];
    float scale;
    int unknown108;
    SceneLightingPayload *payload;
};
struct SceneMaskGlobals {
    char prefix[0x3E04];
    unsigned int mask;
    char pad3E08[0x3ED0 - 0x3E08];
    qword value;
};
extern "C" char D_00475480[];
extern "C" void func_0023CBE0(void *);
extern "C" void func_0018E800(void *, qword, MATRIX4 *, float, float,
                             SceneLightingPayload *);
typedef char CheckMaskedTransform110[sizeof(SceneMaskedTransform) == 0x110 ? 1 : -1];

extern "C" void func_0023CC40(SceneMaskedTransform *object)
{
    SceneMaskGlobals *game = (SceneMaskGlobals *)D_00475480;
    if (object->mask & game->mask) {
        func_0023CBE0(object);
        func_0018E800((char *)object + 0x70, game->value, 0,
                      object->scale, object->scale, object->payload);
    }
}
