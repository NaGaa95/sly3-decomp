// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
#include "gain_control_api.h"
}
class SavedOptionReference {
public:
    CRef value;
    SavedOptionReference(const SavedOptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~SavedOptionReference() { Drop(); }
};
struct SavedOptionKey;
struct SavedOptionGlobals {
    char prefix[0x4198];
    SavedOptionKey *first, *second, *third, *fourth;
};
typedef char CheckSavedOptionRef8[sizeof(SavedOptionReference) == 8 ? 1 : -1];
extern "C" {
extern SavedOptionGlobals D_00475480;
extern char D_00474FF0[];
extern int D_00475000;
SavedOptionReference func_002BC010(SavedOptionKey *, unsigned char *);
void func_002489E0(void *, int);
}
static inline int ReadSavedInteger(SavedOptionKey *key, unsigned char *buffer)
{
    SavedOptionReference reference = func_002BC010(key, buffer);
    return reference.value.payload.integer;
}
static inline float ReadSavedFloat(SavedOptionKey *key, unsigned char *buffer)
{
    SavedOptionReference reference = func_002BC010(key, buffer);
    return reference.value.payload.real;
}
extern "C" void func_0021D360(void *rawBuffer)
{
    unsigned char *buffer = (unsigned char *)rawBuffer;
    if (D_00475480.first)
        func_002489E0(D_00474FF0, ReadSavedInteger(D_00475480.first, buffer));
    if (D_00475480.second)
        func_00248A78(D_00474FF0, 1, 1.0f - ReadSavedFloat(D_00475480.second, buffer), 1);
    if (D_00475480.third) {
        func_00248A78(D_00474FF0, 0, 1.0f - ReadSavedFloat(D_00475480.third, buffer), 1);
        func_00248A78(D_00474FF0, 3, 1.0f - ReadSavedFloat(D_00475480.third, buffer), 1);
    }
    if (D_00475480.fourth)
        D_00475000 = ReadSavedInteger(D_00475480.fourth, buffer);
}
