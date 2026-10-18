// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"

struct LabelColorBytes { unsigned char r, g, b, a; };
struct LabelColor {
    union { LabelColorBytes bytes; unsigned int word; };
    LabelColor() {}
    LabelColor(unsigned int value) { word = value; }
    LabelColor(const LabelColor &value) { bytes = value.bytes; }
};
struct LabelBox {
    float x, y, width, height;
    LabelColor color;
    int horizontal, vertical;
    void SetPosition(float x, float y) __asm__("func_002BC878");
    void SetSize(float width, float height) __asm__("func_002BC888");
    void SetColor(LabelColor *color) __asm__("func_002BC898");
    void SetHorizontal(int value) __asm__("func_002BC8B0");
    void SetVertical(int value) __asm__("func_002BC8B8");
    LabelBox(float x, float y, float width, float height, unsigned int packed_color = 0xFFC0C0C0) {
        SetPosition(x, y);
        SetSize(width, height);
        LabelColor color(packed_color);
        SetColor(&color);
        SetHorizontal(0);
        SetVertical(0);
    }
};
struct LabelRange { float minimum, maximum; };
struct LabelView {
    char opaque000[0x138];
    float scale;
    char opaque13C[0x144 - 0x13C];
    float near;
};
struct LabelFont {
    char opaque000[0x8C];
    float width, height;
    char opaque94[0x1B0 - 0x94];
};

extern "C" {
extern LabelRange D_003258B0;
qword func_001678C8(void *context, qword value);
float func_0011EE68(LabelRange *range, float value);
void *func_00264880(void *receiver, const unsigned short *text, float scale);
void func_00265480(void *font, LabelBox *box, int layer);

void func_002099A8(LabelView *view, qword point, const unsigned short *text, int unused,
                   LabelColor *color, float scale)
{
    qword screen = func_001678C8(view, point);
    float depth = PackedVectorZ(screen);
    if (depth < view->near)
        return;
    float size = scale * (640.0f / (view->scale * depth));
    LabelFont font;
    func_00264880(&font, text, func_0011EE68(&D_003258B0, size));
    LabelBox box(0.0f, 0.0f, 640.0f, 480.0f, 0xFF808080);
    float x = PackedVectorX(screen) * 0.5f + 0.5f;
    float y = 0.5f - PackedVectorY(screen) * 0.5f;
    box.x = x * 640.0f - font.width * 0.5f - 8.0f + 8.0f;
    box.y = y * 480.0f - font.height - 16.0f + 8.0f;
    box.width = font.width + 16.0f;
    box.height = font.height + 16.0f;
    LabelColor tint(*color);
    box.color.bytes = tint.bytes;
    func_00265480(&font, &box, 14);
}
}
