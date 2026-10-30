// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct P { unsigned char pad[0x4CC]; int n4CC; };
struct Self { unsigned char pad[0x10]; struct P *p10; };
extern "C" {
extern qword D_00317560;
void *memset(void *p, int c, unsigned int n);
void func_00241150(struct P *p, int n);
int func_001C0B70(int id, void *buf, int n);
void func_00240CB0(struct P *p, int a, struct P *q, int b, int c, int d, qword e, qword f, int g);
int func_00238AD8(struct Self *self, int msg, int arg);
}
struct F { int kind; int arg; int rest[2]; F() { memset(this, 0, sizeof *this); } };
extern "C" void func_0019A2D0(struct Self *self, struct F *f);
extern "C" int func_0019A780(struct Self *self, int msg, int arg)
{
    switch (msg) {
    case 0xD: case 0xE: case 0xF: case 0x10: case 0x11: {
        int kind;
        switch (msg) {
        case 0xD: kind = 8; break;
        case 0x11: kind = 7; break;
        case 0xF: kind = 9; break;
        case 0xE: kind = 0xA; break;
        case 0x10: kind = 0xB; break;
        }
        struct F f;
        f.kind = kind;
        f.arg = arg;
        func_0019A2D0(self, &f);
        return 1;
    }
    case 0x12: {
        int buf[8];
        func_00241150(self->p10, 0);
        if (func_001C0B70(self->p10->n4CC, buf, 3)) {
            struct F f;
                f.kind = 0x11;
            f.arg = (int)buf;
            func_0019A2D0(self, &f);
        } else {
            func_00240CB0(self->p10, 0, self->p10, 0x800, 10, 1, D_00317560, D_00317560, 0);
        }
        break;
    }
    case 0x13: {
        struct F f;
        f.kind = 0x15;
        f.arg = arg;
        func_0019A2D0(self, &f);
        break;
    }
    }
    return func_00238AD8(self, msg, arg);
}
