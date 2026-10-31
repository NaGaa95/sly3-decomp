// SLY3_CFLAGS: -Os -G0 -ffast-math
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Anchor { unsigned char prefix[0xC]; struct Method *methods; };
struct RangeSelf {
    unsigned char prefix0[0xC];
    struct Method *methods;
    struct Anchor *anchor;
    unsigned char gap14[0x44 - 0x14];
    float reach;
    float near;
    float far;
    unsigned char gap50[0x60 - 0x50];
    qword position;
};
void func_00238978(void *self);

void func_001D8070(struct RangeSelf *self)
{
    struct Anchor *anchor;
    struct Frame *frame;
    func_00238978(self);
    anchor = self->anchor;
    frame = ((struct Frame *(*)(void *))anchor->methods[36].function)((char *)anchor + anchor->methods[36].adjustment);
    {
        float reach = self->reach;
        float reachMin = 100.0f;
        float quarter, nearCap = 25.0f, farCap = 60.0f;
        self->position = frame->position;
        reach = reach > reachMin ? reach : reachMin;
        quarter = reach * 0.25f;
        self->reach = reach;
        self->near = quarter < nearCap ? quarter : nearCap;
        self->far = reach < farCap ? reach : farCap;
    }
    ((void (*)(void *, int))self->methods[16].function)((char *)self + self->methods[16].adjustment, 0);
}
