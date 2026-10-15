// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class SavedOptionReference {
public:
    CRef value;
    SavedOptionReference(const SavedOptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~SavedOptionReference() { Drop(); }
};
struct SavedOptionKey;
struct ScreenOptionGlobals {
    char prefix[0x41A8];
    SavedOptionKey *first, *second;
};
typedef char CheckScreenOptionRef8[sizeof(SavedOptionReference) == 8 ? 1 : -1];
extern "C" {
extern ScreenOptionGlobals D_00475480;
extern char D_0036DBE0[];
SavedOptionReference func_002BC010(SavedOptionKey *, unsigned char *);
void func_00196818(void *, float, float);
void func_00196880(void *, float, float);
}
static inline float ReadScreenValue(SavedOptionKey *key, unsigned char *buffer)
{
    SavedOptionReference reference = func_002BC010(key, buffer);
    return reference.value.payload.real;
}
extern "C" void func_0021D4C8(void *rawBuffer)
{
    unsigned char *buffer = (unsigned char *)rawBuffer;
    if (D_00475480.first && D_00475480.second) {
        func_00196818(D_0036DBE0,
            ReadScreenValue(D_00475480.first, buffer),
            ReadScreenValue(D_00475480.second, buffer));
    }
}
extern "C" void func_0021D570(void *rawBuffer)
{
    unsigned char *buffer = (unsigned char *)rawBuffer;
    if (D_00475480.first && D_00475480.second) {
        func_00196880(D_0036DBE0,
            ReadScreenValue(D_00475480.first, buffer),
            ReadScreenValue(D_00475480.second, buffer));
    }
}
