// Build the status line text: the fixed message while the lock flag is set, otherwise the save hint (with the option-dependent label), and then, when more than one id is available, the label of the id cycling with time (the ids whose label is non-empty rotate every 1.75 seconds, shown for the first 1.5).
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
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
struct SaveSelectionView {
    unsigned char opaque00[0x13950];
    void *selectedBlock;
    void *pendingBlock;
};
struct IdList {
    int count;
    int *ids;
};
struct Host {
    unsigned char pad00[0x4C];
    float startTime;
};
struct Clock { unsigned char pad[0x40]; float now; };
extern "C" {
extern long D_0036F790;
extern unsigned char D_00475480[];
extern unsigned char D_0046FC30[];
extern unsigned char D_00375290[];
extern KEY *D_004794EC;
extern int D_0036B120;
extern const char *D_00349410[];
extern const char D_00326188[];
extern Clock D_0036BB98;
unsigned short *func_00150630(void *game, int name);
void func_00271730(unsigned short *text, unsigned short *string);
void func_00271780(unsigned short *text, unsigned short *string);
unsigned short *func_00271828(unsigned short *text, const char *literal);
int func_00221AC0(void *object);
void func_0011C2E0(int *count, int **ids);
float func_0011EDB8(float value, float modulus);
}
OptionReference QueryOption(KEY *, unsigned char *) __asm__("func_002BC010");
static inline float ReadFloat(KEY *key, unsigned char *p)
{
    return QueryOption(key, p).value.payload.real;
}
extern "C" void func_00222140(unsigned short *text, int unused, Host *host)
{
    if (D_0036F790 == 1) {
        func_00271730(text, func_00150630(D_00475480, 0x12));
        return;
    }
    if (!func_00221AC0(D_0046FC30)) {
        float value = 0.0f;
        void *block = ((SaveSelectionView *)D_00375290)->pendingBlock;
        if (block)
            value = ReadFloat(D_004794EC, (unsigned char *)block);
        int name = 0xD;
        if (value != 0.0f) name = 0xE;
        func_00271730(text, func_00150630(D_00475480, name));
        func_00271828(text, D_00326188);
        func_00271780(text, func_00150630(D_00475480, 0x11));
    }
    {
        struct { int candidates[16]; IdList list; } pick;
        int start;
        int n;
        int i;
        func_0011C2E0(&pick.list.count, &pick.list.ids);
        if (pick.list.count < 2) return;
        start = 0;
        n = 0;
        for (i = 0; i < pick.list.count; i++) {
            if (pick.list.ids[i] == D_0036B120) {
                start = i;
                break;
            }
        }
        for (i = 0; i < pick.list.count; i++) {
            int id = pick.list.ids[(i + start) % pick.list.count];
            if (D_00349410[id])
                pick.candidates[n++] = id;
        }
        if (n > 0) {
            float cycle = func_0011EDB8(D_0036BB98.now - host->startTime, (float)n * 1.75f);
            if (func_0011EDB8(cycle, 1.75f) >= 1.5f) return;
            {
                int index = (int)(cycle * 0.5714286f) % n;
                if (index >= 0 && index < n) {
                    func_00271828(text, D_00326188);
                    func_00271828(text, D_00349410[pick.candidates[index]]);
                }
            }
        }
    }
}
