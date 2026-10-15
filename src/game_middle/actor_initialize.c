// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Initialize the original CID52 receiver and its embedded references.
// Existing word setters receive the actual 32-bit receiver address.
#include "actor_state_resource_api.h"

#define Word(p, o) (*(int *)((char *)(p) + (o)))
#define Float(p, o) (*(float *)((char *)(p) + (o)))

struct S { int a; char pad[0x8C]; int b; float g, h; };
void func_00152218(void *);
void func_00258930(struct S *, int, int);
void func_0024F188(void *, float);
int func_001407A8(void *, int);
void func_002081E8(void *);
extern int D_0036DBE0;

void func_001AA118(void *p)
{
    void *block;
    func_00152218(p);
    Word(p, 0x19E0) = -1;
    Word(p, 0x19E8) = -1;
    Float(p, 0x1AAC) = 15.0f;
    Word(p, 0x1114) = 0x6F;
    func_00258930((struct S *)((char *)p + 0x1470), (int)p, 0x6F);
    func_00258930((struct S *)((char *)p + 0x1C90), (int)p, Word(p, 0x1114));
    {
        float minimum = -100.0f, maximum = 100.0f, width = 50.0f,
              base = -10.0f, limit = 250.0f, second = 1.0f, third = 4500.0f;
        block = (char *)p + 0x1180;
        Float(p, 0x1170) = minimum;
        Float(p, 0x1174) = maximum;
        Float(p, 0x1178) = width;
        Float(p, 0x117C) = base;
        Float(p, 0x1180) = limit;
        Float(block, 0xC) = third;
        Float(block, 0x8) = second;
        Word(block, 0x4) = 0;
    }
    func_0024F188(p, 1.6f);
    func_001407A8((char *)p + 0x1E90, (int)p);
    Word(p, 0x164) = 1;
    Float(p, 0x1130) = 200.0f;
    Word(p, 0x1110) = 0x2EFF;
    if ((D_0036DBE0 ^ 2) == 0)
        Word(p, 0x1110) = 0x2EFB;
    Word(p, 0x294) = 0xFC;
    func_002081E8((char *)p + 0x18F0);
    D_00370AC0 = p;
}
