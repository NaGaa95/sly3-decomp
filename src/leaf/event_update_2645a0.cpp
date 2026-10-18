// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct ColorBytes {
    unsigned char r, g, b, a;
};

struct Color {
    unsigned char r, g, b, a;
    Color(const Color &color) {
        *(ColorBytes *)this = *(const ColorBytes *)&color;
    }
} __attribute__((aligned(16)));

struct Matrix2D {
    float a[6];
} __attribute__((aligned(16)));

struct FrameOwner;
struct Manager {
    char pad[0x74];
    FrameOwner *records;
};

struct Source {
    int unused;
    int kind;
    Manager *manager;
    int id;
    int index;
    Matrix2D *matrix;
};

struct Event {
    char pad[0x58];
    int selection;
};

static inline Matrix2D Mul(const Matrix2D &q, const Matrix2D &n)
{
    float m0 = q.a[0], m1 = q.a[1], m2 = q.a[2];
    float m3 = q.a[3], m4 = q.a[4], m5 = q.a[5];
    Matrix2D result;
    result.a[0] = m0 * n.a[0] + m1 * n.a[2];
    result.a[1] = m0 * n.a[1] + m1 * n.a[3];
    result.a[2] = m2 * n.a[0] + m3 * n.a[2];
    result.a[3] = m2 * n.a[1] + m3 * n.a[3];
    result.a[4] = m4 * n.a[0] + m5 * n.a[2] + n.a[4];
    result.a[5] = m4 * n.a[1] + m5 * n.a[3] + n.a[5];
    return result;
}

extern "C" void func_00267608(float, FrameOwner *, int, Matrix2D *, Color, Color);

extern "C" void func_002645A0(float delta, Source *source, Event *event,
                                Matrix2D *matrix, Color first, Color second)
{
    if (source->kind == 4) {
        Matrix2D transformed;
        Matrix2D *selected;
        if (source->matrix) {
            transformed = Mul(*matrix, *source->matrix);
            selected = &transformed;
        } else {
            selected = matrix;
        }
        func_00267608(delta, (FrameOwner *)((char *)source->manager->records +
                                    source->index * 0x30),
                     event->selection, selected, first, second);
    }
}
