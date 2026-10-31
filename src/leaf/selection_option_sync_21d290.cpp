// Write the stored selection (when set) to the selection option and refresh it from the option's current value.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
}
class SelectionReference {
public:
    CRef value;
    SelectionReference(int selection) { value.tag=0x13; value.payload.integer=selection; }
    SelectionReference(const SelectionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~SelectionReference() { Drop(); }
};
struct KEY;
struct Game { unsigned char prefix[0x4194]; KEY *selectionKey; };
extern "C" {
extern Game D_00475480;
extern int D_003493A0;
int func_0011C330(void);
void func_0011C268(int selection);
SelectionReference QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
SelectionReference AssignOption(KEY *, const SelectionReference &, unsigned char *) __asm__("func_002BC050");
}
static inline void WriteOption(KEY *key, const SelectionReference &value, unsigned char *context)
{
    SelectionReference argument(value);
    AssignOption(key, argument, context);
}
static inline int ReadInteger(KEY *key, unsigned char *context)
{
    return QueryOption(key, context).value.payload.integer;
}
extern "C" void func_0021D290(unsigned char *context)
{
    if (!D_00475480.selectionKey) return;
    if (func_0011C330() < 2) return;
    if (D_003493A0 != -1) {
        SelectionReference value(D_003493A0);
        WriteOption(D_00475480.selectionKey, value, context);
    }
    func_0011C268(ReadInteger(D_00475480.selectionKey, context));
}
