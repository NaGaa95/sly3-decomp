// Reference: Sly 2 BuildClutGifs__FP4CLUTiP4GIFS.cpp; actual packed Sly 3 count.
// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct ClutColorHeader {
    ulong reserved0 : 7;
    unsigned short color_count : 9;
    ulong reserved16 : 48;
};
struct ClutTransferView {
    unsigned int reserved0[2];
    struct ClutColorHeader color_header;
    int quadword_count;
};
typedef char ClutHeaderWidth[(sizeof(struct ClutColorHeader) == 8) ? 1 : -1];
void func_00196D28(int, int, int, int, int, int, void *);

void func_00236150(struct ClutTransferView *clut, int block, void *gifs)
{
    int width = clut->color_header.color_count > 16 ? 16 : 8;
    int height = ((clut->color_header.color_count + (width - 1)) & -width) / width;
    func_00196D28(block, 1, 0, width, height, clut->quadword_count, gifs);
}
