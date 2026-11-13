// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// func_00221EC0 (agent A93): reset handler - clears p+0x50, writes the real option 0.0 to the key at D_004794EC (same
// CRef write pattern as src/engine/subject_options_187d30.cpp), then calls func_00156768(x,1) for each non-null
// *D_00344050[i] (count D_00344068) and finishes with func_0018AB08(D_00468D30). No Sly 2 counterpart.
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionReference {
public:
    CRef value;
    OptionReference(float real) { value.tag = 0x14; value.payload.real = real; }
    OptionReference(const OptionReference &) __asm__("func_0012AF00");
    void Drop() __asm__("func_0012BC20");
    ~OptionReference() { Drop(); }
};
struct KEY;
extern "C" {
extern unsigned char D_00468D30[];
extern KEY *D_004794EC;
extern int **D_00344050[];
extern int D_00344068;
OptionReference AssignOption(KEY *, const OptionReference &, unsigned char *) __asm__("func_002BC050");
void func_00156768(int *, int);
void func_0018AB08(unsigned char *);
void func_00221EC0(char *p);
}
static inline void WriteOption(KEY *key, const OptionReference &value, void *context)
{
    OptionReference argument(value);
    const OptionReference &result = AssignOption(key, argument, (unsigned char *)context);
}
static inline void WriteReal(KEY *key, float real)
{
    unsigned char *context = D_00468D30;
    OptionReference value(real);
    WriteOption(key, value, context);
}
extern "C" void func_00221EC0(char *p)
{
    *(int *)(p + 0x50) = 0;
    WriteReal(D_004794EC, 0.0f);
    for (int i = 0; i < D_00344068; i++) {
        int *x = *D_00344050[i];
        if (x) func_00156768(x, 1);
    }
    func_0018AB08(D_00468D30);
}
