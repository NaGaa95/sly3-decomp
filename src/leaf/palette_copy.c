// SLY3_CFLAGS: -Os -G0
struct ClutPixel { unsigned char red, green, blue, alpha; };
struct PaletteRawHeader { unsigned char bytes[16]; };
struct PaletteCountBits {
    unsigned long reserved0 : 7;
    unsigned short color_count : 9;
    unsigned long reserved16 : 48;
};
union PaletteMetadata {
    struct PaletteCountBits bits;
    struct { unsigned int lower; struct ClutPixel *data; } pointer;
};
struct PaletteHeaderFields {
    unsigned int reserved0[2];
    union PaletteMetadata metadata;
};
union PaletteHeader {
    struct PaletteRawHeader raw;
    struct PaletteHeaderFields fields;
};
struct PaletteCopyView {
    union PaletteHeader header;
    unsigned int quadword_count;
};
typedef char ClutPixelWidth[(sizeof(struct ClutPixel) == 4) ? 1 : -1];
typedef char PaletteRawWidth[(sizeof(struct PaletteRawHeader) == 16) ? 1 : -1];
typedef char PaletteMetadataWidth[(sizeof(union PaletteMetadata) == 8) ? 1 : -1];
typedef char PaletteHeaderWidth[(sizeof(union PaletteHeader) == 16) ? 1 : -1];
typedef char PalettePointerWidth[(sizeof(void *) == 4) ? 1 : -1];
void func_00236908(void *color);
struct PaletteCopyView *func_00234430(struct PaletteCopyView *palette,
                                    const struct PaletteRawHeader *source)
{
    struct ClutPixel *color;
    palette->header.raw = *source;
    for (color = palette->header.fields.metadata.pointer.data;
         (unsigned int)color <
             (unsigned int)palette->header.fields.metadata.pointer.data +
             palette->header.fields.metadata.bits.color_count * sizeof(struct ClutPixel);
         ++color)
        func_00236908(color);
    palette->quadword_count =
        (palette->header.fields.metadata.bits.color_count * sizeof(struct ClutPixel) + 15) >> 4;
    return palette;
}
