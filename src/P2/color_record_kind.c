// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct COLOR_FOUR_WORDS { int words[4]; };
union COLOR_KIND_VALUE { float scalar; struct COLOR_FOUR_WORDS words; };
struct COLOR_KIND_RECORD {
    union COLOR_KIND_VALUE value;
    unsigned char reserved10[0x14];
    int kind;
};
struct COLOR_KIND_CONTEXT {
    unsigned char reserved00[0x1C];
    struct COLOR_KIND_RECORD *extra;
};
struct COLOR_KIND_WRAPPER {
    unsigned char reserved00[0x20];
    struct COLOR_KIND_CONTEXT *context;
};
extern struct COLOR_FOUR_WORDS D_00347F20;
extern float D_00347F30;
void *func_001FDC18(void *, int);

void func_001FDB80(void *receiver, int kind)
{
    struct COLOR_KIND_WRAPPER *wrapper = receiver;
    struct COLOR_KIND_RECORD *extra;
    if (wrapper->context->extra->kind == kind)
        return;
    extra = func_001FDC18(receiver, 1);
    extra->kind = kind;
    switch (kind) {
    case 2:
        extra->value.words = D_00347F20;
        break;
    case 1:
        extra->value.scalar = D_00347F30;
        break;
    }
}
