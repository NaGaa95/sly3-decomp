// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Anchor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x260 - 0x10];
    qword offset;
};
extern char D_00317490[];
void func_001FE728(void *object, int flag);
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

void func_001E2A20(struct Anchor *self, struct Object *object)
{
    if (object) {
        struct Method *place = &object->methods[34];
        void *receiver = (char *)object + place->adjustment;
        struct Frame *frame = ((struct Frame *(*)(void *))self->methods[36].function)((char *)self + self->methods[36].adjustment);
        ((void (*)(void *, qword))place->function)(receiver, Add(frame->position, self->offset));
        ((void (*)(void *, void *))object->methods[35].function)((char *)object + object->methods[35].adjustment, D_00317490);
        func_001FE728(object, 1);
    }
}
