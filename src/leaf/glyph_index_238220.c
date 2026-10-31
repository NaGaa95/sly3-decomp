// SLY3_CFLAGS: -Os -G0
// Glyph index of a printable ASCII character (0 for others): punctuation ranges index a 4-byte-entry table directly, digits,
// upper and lower case letters are offset from a per-group base glyph.
struct GlyphEntry { unsigned short base; unsigned short first; };
extern struct GlyphEntry D_00349710[];
extern struct GlyphEntry D_00349798[];
unsigned short func_00238220(unsigned char c)
{
    int punct = 0;
    int group;
    if (c >= 0x20 && c < 0x30)
        punct = 1;
    else if (c >= 0x30 && c < 0x3A)
        group = 0;
    else if (c >= 0x3A && c < 0x41)
        punct = 0xB;
    else if (c >= 0x41 && c < 0x5B)
        group = 1;
    else if (c >= 0x5B && c < 0x61)
        punct = 0x25;
    else if (c >= 0x61 && c < 0x7B)
        group = 2;
    else if (c >= 0x7B && c < 0x7F)
        punct = 0x3F;
    else
        return 0;
    if (!punct)
        return D_00349798[group].base + c - D_00349798[group].first;
    {
        int base = punct + 0x1F;
        return D_00349710[c - base].base;
    }
}
