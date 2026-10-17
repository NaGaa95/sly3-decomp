// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class BlockReference {
public:
    CRef value;
    BlockReference() { value.tag = -1; }
    BlockReference(const BlockReference &) __asm__("func_0012AF00");
    BlockReference &operator=(const BlockReference &) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~BlockReference() { Drop(); }
};
extern "C" void func_001D2798(void *frame, int flags);
class BlockFrame {
    int storage[4];
public:
    BlockFrame() __asm__("func_001D2770");
    ~BlockFrame() { func_001D2798(this, 2); }
};
struct BlockKey;
struct BlockTrie;
struct BlockGlobals {
    char prefix[0x4194];
    BlockKey *special;
    BlockKey *first, *second, *third, *fourth, *fifth, *sixth, *seventh;
};
typedef char CheckBlockRef8[sizeof(BlockReference) == 8 ? 1 : -1];
typedef char CheckBlockFrame16[sizeof(BlockFrame) == 16 ? 1 : -1];
extern "C" {
extern BlockGlobals D_00475480;
extern BlockTrie D_004793C8;
extern int D_0036B120;
int func_0021C198(BlockTrie *, unsigned char *);
BlockReference func_0021C338(BlockTrie *, BlockKey *, unsigned char *);
BlockReference func_002BC050(BlockKey *, const BlockReference &, unsigned char *);
void *func_00292034(void *, int, unsigned int);
void func_0018AD58(void);
}
static inline BlockReference ReadKey(BlockKey *key, unsigned char *block)
{
    return func_0021C338(&D_004793C8, key, block);
}
static inline BlockReference WriteKey(BlockKey *key, const BlockReference &value, unsigned char *block)
{
    return func_002BC050(key, value, block);
}
static inline void WriteInteger(BlockKey *key, int number, unsigned char *block)
{
    BlockReference value;
    value.value.tag = 0x13;
    value.value.payload.integer = number;
    BlockReference copy = value;
    WriteKey(key, copy, block);
}
extern "C" void func_0021D010(unsigned char *block, int retainValues)
{
    BlockFrame frame;
    BlockKey *keys[7] = { D_00475480.seventh, D_00475480.first, D_00475480.second, D_00475480.third, D_00475480.fourth, D_00475480.fifth, D_00475480.sixth };
    BlockReference saved[7];
    if (retainValues && !func_0021C198(&D_004793C8, block))
        retainValues = 0;
    if (retainValues) {
        for (unsigned int i = 0; i < 7; ++i)
            saved[i] = ReadKey(keys[i], block);
    }
    func_00292034(block, 0, 0x6800);
    func_0018AD58();
    if (retainValues) {
        for (unsigned int i = 0; i < 7; ++i)
        {
            BlockKey **key = &keys[i];
            BlockReference copy = saved[i];
            WriteKey(*key, copy, block);
        }
    }
    if (D_00475480.special)
        WriteInteger(D_00475480.special, D_0036B120, block);
}
