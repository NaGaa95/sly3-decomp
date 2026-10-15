// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EXTRA_TRIPLE { int words[3]; };
union EXTRA_VALUE { int word; struct EXTRA_TRIPLE triple; };
struct EXTRA_KIND_RECORD {
    union EXTRA_VALUE value;
    unsigned char reserved0C[0x10];
    int kind;
};
struct EXTRA_KIND_CONTEXT {
    unsigned char reserved00[0x1C];
    struct EXTRA_KIND_RECORD *extra;
};
struct EXTRA_KIND_OWNER {
    unsigned char reserved00[0x20];
    struct EXTRA_KIND_CONTEXT *context;
};
extern int D_00347F60;
extern struct EXTRA_TRIPLE D_00347F68;
extern int D_00347F78;
extern struct EXTRA_TRIPLE D_00347F80;
void *func_001FE0C0(void *, int);

void func_001FDFD0(void *receiver, int kind)
{
    struct EXTRA_KIND_OWNER *owner = receiver;
    struct EXTRA_KIND_RECORD *extra;
    if (owner->context->extra->kind == kind)
        return;
    extra = func_001FE0C0(receiver, 1);
    extra->kind = kind;
    switch (kind) {
    case 2:
        extra->value.word = D_00347F60;
        break;
    case 7:
        extra->value.triple = D_00347F68;
        break;
    case 1:
        extra->value.word = D_00347F78;
        break;
    case 10:
        extra->value.triple = D_00347F80;
        break;
    }
}
