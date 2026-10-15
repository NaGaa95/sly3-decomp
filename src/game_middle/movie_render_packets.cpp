// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/gifs.h"

struct MovieColorBytes { unsigned char r, g, b, a; };
struct MovieColor {
    union { MovieColorBytes bytes; unsigned int word; };
    MovieColor() {}
    MovieColor(unsigned int value) { word = value; }
    MovieColor(const MovieColor &value) { bytes = value.bytes; }
};
struct MovieTextStorage { unsigned char opaque[0x180]; } __attribute__((aligned(16)));
struct MovieTextBox {
    float x, y, width, height;
    MovieColor color;
    int horizontal, vertical;
    void SetPosition(float x, float y) __asm__("func_002BC878");
    void SetSize(float width, float height) __asm__("func_002BC888");
    void SetColor(MovieColor *color) __asm__("func_002BC898");
    void SetHorizontal(int value) __asm__("func_002BC8B0");
    void SetVertical(int value) __asm__("func_002BC8B8");
    MovieTextBox(float x, float y, float width, float height,
                 unsigned int packed_color = 0xFFC0C0C0) {
        SetPosition(x, y);
        SetSize(width, height);
        MovieColor color(packed_color);
        SetColor(&color);
        SetHorizontal(0);
        SetVertical(0);
    }
};
struct MovieTextEntry { int opaque00, key; };
struct MovieRenderState {
    unsigned char opaque00[0x104];
    MovieTextEntry *entry;
    unsigned char opaque108[8];
    unsigned char *packet_buffer;
    int opaque114;
    int width, height;
};
struct MovieScreenView {
    void *vtable;
    int width, height;
    unsigned char opaque0C[0x1C - 0xC];
    int texture_page;
};

extern "C" {
extern unsigned char D_0036DBE0[], D_00389AB0[];
extern QW D_0036E2A0[];
extern void *D_0036BF00;
int func_002BC640(void *screen, int value);
int func_002BC648(void *screen, int value);
int func_002BC668(void *screen, int value);
int func_002BC670(void *screen, int value);
void func_00180980(void *font, float x, float y);
void func_001809E0(void *font);
void *func_0025E870(void *table, int key);
void *func_00181330(void *output, void *text, void *font);
float func_00181A90(void *text, float width);
float func_00181AD8(void *text);
void func_00209798(MovieColor color, GIFS *packets, float x, float y,
                   float right, float bottom);
void func_00181B60(void *text, MovieTextBox *box, MovieTextBox *clip, GIFS *packets);

static inline int CenteredX(MovieScreenView *screen, int value)
{
    int offset = 2048 - func_002BC640(screen, screen->width) / 2;
    return value + offset;
}
static inline int CenteredY(MovieScreenView *screen, int value)
{
    int offset = 2048 - func_002BC648(screen, screen->height) / 2;
    return value + offset;
}

void func_001DB8C8(MovieRenderState *state)
{
    GIFS packets;
    packets.AllocStatic(0x200, (QW *)(state->packet_buffer + 0x41BC00));
    packets.AddDmaRefs(10, D_0036E2A0);
    packets.AddDmaCnt();
    packets.AddPrimPack(6, 1, 0xE);
    MovieScreenView *screen = (MovieScreenView *)D_0036DBE0;
    packets.PackAD(6, 0xA80000000L | (screen->texture_page * 3 | 0x28030000));
    packets.PackAD(0x14, 0x61);
    packets.PackAD(8, 5);
    packets.PackAD(0x42, 0x44);
    packets.PackAD(0x47, 0x31001);
    packets.AddPrimPack(0x116, 4, 0x4343);
    packets.PackUV(8, 8);
    packets.PackXYZF(
        func_002BC668(screen, CenteredX(screen, 0)),
        func_002BC670(screen, CenteredY(screen, 0)), 0, 0);
    packets.PackUV((state->width << 4) | 8, (state->height << 4) | 8);
    packets.PackXYZF(
        func_002BC668(screen, CenteredX(screen, func_002BC640(screen, screen->width))),
        func_002BC670(screen, CenteredY(screen, func_002BC648(screen, screen->height))), 0, 0);
    packets.AddPrimPack(0, 1, 0xE);
    packets.PackAD(0x61, 0);
    packets.AddPrimEnd();
    packets.AddDmaEnd();
    packets.Detach(0, 0);
    if (state->entry) {
        packets.AllocStatic(0x200, (QW *)(state->packet_buffer + 0x41DC00));
        packets.AddDmaCnt();
        func_00180980(D_0036BF00, 0.8f, 0.8f);
        MovieTextStorage text;
        func_00181330(&text, func_0025E870(D_00389AB0, state->entry->key), D_0036BF00);
        float height = func_00181A90(&text, 320.0f);
        float width = func_00181AD8(&text);
        MovieTextBox box(320.0f - width * 0.5f, 464.0f - height, width, height);
        MovieColor color;
        MovieTextBox *draw_box = &box;
        draw_box->horizontal = 1;
        color.word = 0x80000000;
        func_00209798(color, &packets, box.x, box.y,
                      box.x + box.width, box.y + box.height);
        func_00181B60(&text, draw_box, 0, &packets);
        func_001809E0(D_0036BF00);
        packets.AddPrimPack(0, 1, 0xE);
        packets.PackAD(0x61, 0);
        packets.AddPrimEnd();
        packets.AddDmaEnd();
        packets.Detach(0, 0);
    }
}
}
