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

struct Frame {
    char pad[0x10];
    int identifier;
};

struct FrameOwner {
    unsigned short count;
    short unused;
    Frame *frames;
    char pad8[8];
    unsigned long stamp;
    float savedTime;
    int savedFrame;
    int requestedFrame;
};

extern "C" unsigned long D_0036BBE0;
extern "C" void func_00267110(FrameOwner *, int, int, void *, float, Color, Color);

extern "C" void func_00267028(FrameOwner *owner, int kind, int slot,
                                void *matrix, Color first, Color second)
{
    float time = 0.0f;
    int frame;
    if (kind == 0x37B) {
        frame = owner->requestedFrame;
        if (frame != -1) {
            owner->requestedFrame = -1;
        } else if (owner->stamp == D_0036BBE0) {
            time = owner->savedTime;
            frame = owner->savedFrame;
        } else {
            owner->savedTime = time;
            frame = 0;
            owner->savedFrame = 0;
        }
    } else {
        for (frame = 0; frame < owner->count; frame++)
            if (owner->frames[frame].identifier == kind)
                break;
        if (frame >= owner->count)
            return;
    }
    func_00267110(owner, frame, slot, matrix, time, first, second);
}
