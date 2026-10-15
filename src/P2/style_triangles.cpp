// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "gifs.h"

struct RGBA { unsigned char r, g, b, a; };
struct COLOR_ENTRY { int n; void *p; struct RGBA c, c2; };
struct StyleTriangle { int indices[3]; };
struct StylePoint { float x, y; };
struct StyleTransform { float a, b, c, d, tx, ty; };
typedef char StyleRgbaSize[sizeof(RGBA) == 4 && __alignof__(RGBA) == 1 ? 1 : -1];
struct COORDINATE_CONVERSION_FIELDS {
    void *vtable;
    int widthSelector;
    int heightSelector;
    int unknownC;
    int divisor;
};
extern "C" {
extern COLOR_ENTRY D_00467B90[5];
extern StylePoint D_00347100[];
extern COORDINATE_CONVERSION_FIELDS D_0036DBE0;
float func_002BE228(COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE230(COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE248(COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE298(COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE2E8(COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE2F8(COORDINATE_CONVERSION_FIELDS *, float);

void func_001F9FB0(GIFS *packet, StyleTransform *transform, float alpha)
{
    packet->AddPrimPack(0, 1, 0xE);
    packet->PackAD(0x47, 0x31001);
    packet->PackAD(0x42, 0x44);
    for (unsigned int i = 0; i < 5; ++i) {
        COLOR_ENTRY *entry = &D_00467B90[i];
        RGBA color;
        packet->AddPrimPack(0, 2, 0xE1);
        color = ((D_0036DBE0.unknownC >> 1) & 1) ? entry->c2 : entry->c;
        color.a = (int)(color.a * alpha);
        packet->PackRGBA(*(uint *)&color);
        packet->PackAD(0, (signed char)color.a >= 0 ? 0x43 : 0x83);
        packet->AddPrimList(1, 4);
        for (int j = 0; j < entry->n; ++j) {
            int *indices = ((StyleTriangle *)entry->p)[j].indices;
            for (int k = 0; k < 3; ++k) {
                StylePoint point = D_00347100[*indices++];
                StylePoint screen;
                screen.x = transform->a * point.x + transform->c * point.y + transform->tx;
                screen.y = transform->b * point.x + transform->d * point.y + transform->ty;
                int x = (int)func_002BE2E8(&D_0036DBE0,
                    func_002BE248(&D_0036DBE0,
                        func_002BE228(&D_0036DBE0,
                            screen.x * (float)D_0036DBE0.widthSelector * 0.0015625f)));
                int y = (int)func_002BE2F8(&D_0036DBE0,
                    func_002BE298(&D_0036DBE0,
                        func_002BE230(&D_0036DBE0,
                            screen.y * (float)D_0036DBE0.heightSelector * 0.0020833334f)));
                packet->ListXYZF(x, y, 0, 0);
            }
        }
    }
}
}
