// SLY3_CFLAGS: -Os -G0
struct Owner {
    unsigned char prefix[0x134];
    void *input;
    unsigned char gap138[0x418 - 0x138];
    void *clip0;
    void *clip1;
    void *playback0;
    void *playback1;
};
int func_00138AC8(void *);
void func_00137688(void **);
unsigned int func_001A7A80(void *, unsigned int, float);
void func_00137588(void *, void *, float, float, int, void **);
void func_00205750(struct Owner *owner)
{
    void **first = &owner->playback0;
    void **second;
    if (*first) {
        if (func_00138AC8(*first))
            func_00137688(first);
    }
    second = &owner->playback1;
    if (*second) {
        if (func_00138AC8(*second))
            func_00137688(second);
    }
    if (func_001A7A80(owner->input, 1, 0.0f))
        func_00137588(owner->clip0, owner, 0.0f, 1.0f, 0, first);
    if (func_001A7A80(owner->input, 2, 0.0f))
        func_00137588(owner->clip1, owner, 0.0f, 1.0f, 0, second);
}
