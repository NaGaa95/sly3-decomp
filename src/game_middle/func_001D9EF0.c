// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Anchor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x260 - 0x10];
    qword offset;
};
struct Mark {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0xCC - 0x10];
    int active;
};
struct Phase {
    unsigned char prefix0[0x10];
    struct Anchor *anchor;
    unsigned char gap14[0x18 - 0x14];
    unsigned char resource[0x50 - 0x18];
    int mode;
    float changed;
};
struct Clock { float time; };
extern struct Clock D_0036BB98;
extern qword D_00317560;
void func_00238AE8(void *resource);
struct Mark *func_00238690(void *table, int id);
void func_00132930(struct Mark *mark, qword position);
void func_00256DF0(void *anchor);
void func_00238AB8(void *phase);
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }

void func_001D9EF0(struct Phase *self, int mode, qword position)
{
    if (mode == self->mode)
        return;
    func_00238AE8(self->resource);
    self->mode = mode;
    self->changed = D_0036BB98.time;
    switch (mode) {
    case 0: {
        struct Mark *mark = func_00238690((char *)self->anchor + 0x29C, 0xCB);
        func_00132930(mark, Add(position, self->anchor->offset));
        mark->active = 1;
        ((void (*)(void *))mark->methods[8].function)((char *)mark + mark->methods[8].adjustment);
        break;
    }
    case 1: {
        struct Anchor *anchor;
        func_00256DF0(self->anchor);
        anchor = self->anchor;
        ((void (*)(void *, qword))anchor->methods[34].function)((char *)anchor + anchor->methods[34].adjustment, position);
        anchor = self->anchor;
        ((void (*)(void *, qword))anchor->methods[40].function)((char *)anchor + anchor->methods[40].adjustment, D_00317560);
        anchor = self->anchor;
        ((void (*)(void *, qword))anchor->methods[41].function)((char *)anchor + anchor->methods[41].adjustment, D_00317560);
        break;
    }
    case -1:
        func_00238AB8(self);
        break;
    }
}
