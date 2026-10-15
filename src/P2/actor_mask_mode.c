// SLY3_ASFIX: engine-local-jumps
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "actor_state_resource_api.h"

typedef struct Mask16 { unsigned char bytes[16]; } Mask16;
static __inline__ Mask16 MaskAnd(const Mask16 *left, const Mask16 *right)
{
    Mask16 result;
    int i;
    for (i = 0; i < 16; ++i)
        result.bytes[i] = left->bytes[i] & right->bytes[i];
    return result;
}
static __inline__ int MaskDifferent(const Mask16 *left, const Mask16 *right)
{
    int i;
    for (i = 0; i < 16; ++i)
        if (left->bytes[i] != right->bytes[i])
            return 1;
    return 0;
}
struct OwnerView { char prefix[0x19C]; unsigned int word19C; };
struct MaskReceiver {
    char prefix[0x2F4];
    Mask16 mask;
    char to_owner[0x4AC - 0x304];
    struct OwnerView *owner;
};
struct P;
extern char D_00475480[];
extern Mask16 D_00467B80;
extern Mask16 D_00475440;
void func_001F17C8(struct P *receiver, int mode);

void func_001F18D0(struct P *receiver)
{
    struct MaskReceiver *p = (struct MaskReceiver *)receiver;
    if (p->owner) {
        void *selected = func_001F4AD0(D_00475480, 0);
        int mode;
        Mask16 masked = MaskAnd(&p->mask, &D_00467B80);
        if (MaskDifferent(&masked, &D_00475440))
            mode = 0;
        else if (p->owner->word19C &&
                 (selected == D_00370AC0 || selected == D_0036B250 || selected == D_0038AE90))
            mode = 2;
        else
            mode = 1;
        func_001F17C8(receiver, mode);
    }
}
