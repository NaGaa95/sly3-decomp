// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
CRef *func_0024B330(CRef *, CRef *, int, int, int *, int *);
}
struct MaskEnumerationBits {
    unsigned char bytes[16];
    MaskEnumerationBits() {}
};
struct ExtractedStatus {
    CRef ref;
    ~ExtractedStatus() { func_0012BC20(&ref); }
};
extern "C" MaskEnumerationBits func_00252B60(int count,const int *indices);
extern "C" MaskEnumerationBits func_00252D80(CRef *values)
{
    int ids[16];
    ExtractedStatus status;
    int count;
    func_0024B330(&status.ref,values,0x100F,16,&count,ids);
    return func_00252B60(count,ids);
}
