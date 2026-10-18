// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions
typedef int Quad __attribute__((mode(TI)));
struct ColorBytes { unsigned char r, g, b, a; };
struct Color {
    unsigned char r, g, b, a;
    Color() {}
    Color(const Color &c) { *(ColorBytes *)this = *(const ColorBytes *)&c; }
    Color &operator=(const Color &c){*(ColorBytes *)this=*(const ColorBytes *)&c;return *this;}
} __attribute__((aligned(16)));
struct PackedMatrix2D { Quad a, b; };
struct DrawParameters { ColorBytes c0; ColorBytes c1; char pad8[8]; PackedMatrix2D q; };
struct FrameSlot { int count;void *items;short savedFrame;short subframe;float time;int active;void *sound; };
struct Frame { char pad[8]; float f8; char padc[8]; };
struct FrameLibrary;
struct FrameOwner { int x0; Frame *frames; FrameSlot *slots; char padc[0x18]; FrameLibrary *library; char pad28[8]; };
struct FrameLibrary { char pad[0x74]; FrameOwner *owners; };
extern "C" int func_00262BD0(FrameLibrary *p, int k, PackedMatrix2D *pq, Color *pc0, Color *pc1, int c, void *ay);
extern "C" void func_002672B8(FrameOwner *p, int i);
extern "C" void func_00267608(float g, FrameOwner *p, int i, PackedMatrix2D *pq, const Color *c0, const Color *c1);
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
extern "C" void func_002673F8(FrameOwner *p, int i, DrawParameters *py, float g)
{
    PackedMatrix2D q;
    Color c0, c1;
    int h = p->slots[i].savedFrame;
    if (h < 0)
        return;
    g = GMin(p->frames[h].f8, GMax(0.0f, g));
    if (py) {
        q = py->q;
        *(ColorBytes *)&c0 = py->c0;
        *(ColorBytes *)&c1 = py->c1;
    } else if (!func_00262BD0(p->library, p - p->library->owners, &q, &c0, &c1, 0, 0)) {
        return;
    }
    func_002672B8(p, i);
    p->slots[i].time = 0.0f;
    p->slots[i].subframe = 0;
    p->slots[i].active = 0;
    Color argument0(c0),argument1(c1);
    func_00267608(0.0f, p, i, &q, &argument0, &argument1);
    p->slots[i].active = 0;
    argument0=c0;Color argument2(c1);
    func_00267608(g, p, i, &q, &argument0, &argument2);
    p->slots[i].active = 1;
}
