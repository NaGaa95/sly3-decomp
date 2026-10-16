// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
typedef int AssetVectorWord __attribute__((mode(TI)));
extern "C" CRef *func_0012AFA0(CRef *, AssetVectorWord);

static inline AssetVectorWord AssetCross3(AssetVectorWord first,
                                         AssetVectorWord second)
{
    AssetVectorWord result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1"
            : "=j"(result) : "j"(first), "j"(second));
    return result;
}

extern "C" CRef *func_00124508(CRef *output, int count,
                              CRef *arguments, EvalFrame *frame)
{
    CRef temporary;
    AssetVectorWord result = AssetCross3(
        *static_cast<AssetVectorWord *>(arguments[0].payload.pointer),
        *static_cast<AssetVectorWord *>(arguments[1].payload.pointer));
    func_0012AFA0(&temporary, result);
    func_0012AF00(output, &temporary);
    func_0012BC20(&temporary);
    return output;
}
