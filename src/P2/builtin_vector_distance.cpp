// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
typedef int AssetDistanceVectorWord __attribute__((mode(TI)));
extern "C" AssetDistanceVectorWord D_00317560;
extern "C" CRef *func_0012B2B0(CRef *, float);

static inline AssetDistanceVectorWord AssetDistanceSubtract(
    AssetDistanceVectorWord first, AssetDistanceVectorWord second)
{
    AssetDistanceVectorWord result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(first), "j"(second));
    return result;
}

static inline AssetDistanceVectorWord AssetDistanceSquaredLength3(
    AssetDistanceVectorWord value)
{
    AssetDistanceVectorWord product, one;
    __asm__("vmul.xyz %0,%2,%2\n\t"
            "vaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\t"
            "vmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(value));
    return product;
}

static inline float AssetDistanceLowFloat(AssetDistanceVectorWord value)
{
    float result;
    __asm__("qmfc2.ni %0,%1" : "=r"(result) : "j"(value));
    return result;
}

static inline AssetDistanceVectorWord AssetDistanceSquareRootX(
    AssetDistanceVectorWord value)
{
    AssetDistanceVectorWord result;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q"
            : "=j"(result) : "j"(value));
    return result;
}

extern "C" CRef *func_001245A8(CRef *output, int count,
                         CRef *arguments, EvalFrame *frame)
{
    CRef temporary;
    temporary.tag = -1;
    if (arguments[1].tag == 0) {
        func_0012B2B0(&temporary, AssetDistanceLowFloat(AssetDistanceSquareRootX(AssetDistanceSquaredLength3(
            AssetDistanceSubtract(
                *static_cast<AssetDistanceVectorWord *>(arguments[0].payload.pointer),
                D_00317560)))));
    } else {
        func_0012B2B0(&temporary, AssetDistanceLowFloat(AssetDistanceSquareRootX(AssetDistanceSquaredLength3(
            AssetDistanceSubtract(
                *static_cast<AssetDistanceVectorWord *>(arguments[0].payload.pointer),
                *static_cast<AssetDistanceVectorWord *>(
                    static_cast<ScriptNode *>(arguments[1].payload.pointer)->ref.payload.pointer))))));
    }
    func_0012AF00(output, &temporary);
    func_0012BC20(&temporary);
    return output;
}
