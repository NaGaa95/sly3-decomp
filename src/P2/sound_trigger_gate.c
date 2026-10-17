// SLY3_CFLAGS: -Os -G0
struct Owner {
    unsigned char prefix[0x134];
    void *input;
    unsigned char gap[0x1CC - 0x138];
    int state;
};
void func_0023C660(void *);
unsigned int func_001A7A80(void *, unsigned int, float);
void *func_002459F8(int);
void func_00244F08(void *, int);
void *func_001F4A80(void *);
void func_00168670(void *, int);
void func_0020FC58(void *);
void func_0020FA10(void *);
void func_0020EE58(struct Owner *owner)
{
    int state;
    func_0023C660(owner);
    state = owner->state;
    if (state < 2) {
        if (state >= 0)
            return;
    }
    if (func_001A7A80(owner->input, 0x200, 0.15f)) {
        func_00244F08(func_002459F8(0x2A), 0);
        func_00168670(func_001F4A80(owner), 0);
    }
    func_0020FC58(owner);
    func_0020FA10(owner);
}
