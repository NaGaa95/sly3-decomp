// SLY3_CFLAGS: -Os -G0
typedef int FontConstructPacket __attribute__((mode(TI)));
struct FontConstructView {
    const unsigned short *text;
    unsigned short *cursor;
    void *font, *primary_font, *alternate_font;
    unsigned int active_color, primary_color, alternate_color;
    unsigned char opaque20[0x20];
    FontConstructPacket parameters0, parameters1;
    int changed;
    float offset_x, offset_y;
    float x, y, width, height;
    float scale_x, scale_y, baseline, scale;
    unsigned char opaque8C[0x198 - 0x8C];
    int vertical_alignment, horizontal_alignment, layer;
};
struct FontBankView { unsigned char opaque00[0x44]; unsigned char *fonts; };
struct FontGameView { unsigned char opaque00[0x4334]; struct FontBankView *font_bank; };
struct COORDINATE_CONVERSION_FIELDS;
struct FontConstructScreen { int mode, width, height; };
extern unsigned char D_0036DBE0[], D_00475480[];
extern FontConstructPacket D_003175A0, D_003175B0;
int func_002BC640(struct COORDINATE_CONVERSION_FIELDS *, int value);
int func_002BC648(struct COORDINATE_CONVERSION_FIELDS *, int value);
void func_00265000(void *receiver);
void func_00264B18(void *receiver, const unsigned short *text);

void *func_00264880(void *receiver, const unsigned short *text, float scale)
{
    struct FontConstructView *font = (struct FontConstructView *)receiver;
    struct FontConstructScreen *screen = (struct FontConstructScreen *)D_0036DBE0;
    font->text = text;
    font->scale_x = 1.0f;
    font->scale_y = 1.0f;
    font->x = 0.0f;
    font->y = 0.0f;
    font->width = 0.0f;
    font->height = 0.0f;
    font->horizontal_alignment = 1;
    font->vertical_alignment = 1;
    font->offset_x = (float)(2048 - func_002BC640(
        (struct COORDINATE_CONVERSION_FIELDS *)screen, screen->width) / 2);
    font->offset_y = (float)(2048 - func_002BC648(
        (struct COORDINATE_CONVERSION_FIELDS *)screen, screen->height) / 2);
    font->scale = scale;
    font->baseline = scale * 51.2f;
    font->layer = 14;
    font->font = font->primary_font = ((struct FontGameView *)D_00475480)->font_bank->fonts;
    font->alternate_font = ((struct FontGameView *)D_00475480)->font_bank->fonts + 0x30;
    font->primary_color = 0x80808080;
    font->parameters0 = D_003175A0;
    font->parameters1 = D_003175B0;
    func_00265000(font);
    func_00264B18(font, 0);
    return font;
}
