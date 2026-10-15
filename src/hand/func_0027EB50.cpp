// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Sly 3 palette selector recovered from Sly 2's RGBA value-returning helper.
// PaletteColor is a four-byte, alignment-one aggregate. Its nontrivial constructor
// preserves the original hidden output pointer A0; kind is the real A1 input.
struct PaletteColor {
    unsigned char red, green, blue, alpha;
    PaletteColor() {}
    PaletteColor(int r, int g, int b, int a)
        : red(r), green(g), blue(b), alpha(a) {}
};
typedef char palette_color_is_four_bytes[sizeof(PaletteColor) == 4 ? 1 : -1];
typedef char palette_color_alignment_is_one[__alignof__(PaletteColor) == 1 ? 1 : -1];
extern "C" PaletteColor func_0027EB50(int kind)
{
    PaletteColor color;
    switch (kind) {
    case 0x34: color = PaletteColor(0x33, 0x66, 0x99, 0x7f); break;
    case 0x36: color = PaletteColor(0x33, 0x99, 0x33, 0x7f); break;
    case 0x35: color = PaletteColor(0x99, 0x33, 0x66, 0x7f); break;
    case 0x3c: color = PaletteColor(0x99, 0x33, 0x33, 0x7f); break;
    default: color = PaletteColor(0x66, 0x66, 0x66, 0x7f); break;
    }
    return color;
}
