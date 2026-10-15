// SLY3_CFLAGS: -Os -G0
typedef unsigned long ulong;
struct TEX0 {
    ulong TBP0 : 14; ulong TBW : 6; ulong PSM : 6; ulong TW : 4; ulong TH : 4; ulong TCC : 1;
    ulong TFX : 2; ulong CBP : 14; ulong CPSM : 4; ulong CSM : 1; ulong CSA : 5; ulong CLD : 3;
};
struct ClutColorHeader {
    ulong reserved0 : 7;
    unsigned short color_count : 9;
    ulong reserved16 : 48;
};
struct ClutTex0View {
    int reserved0[2];
    struct ClutColorHeader color_header;
    ulong reserved10;
    struct TEX0 tex0;
};
typedef char ClutHeaderWidth[(sizeof(struct ClutColorHeader) == 8) ? 1 : -1];
typedef char ClutTex0Width[(sizeof(struct TEX0) == 8) ? 1 : -1];
typedef char ClutViewWidth[(sizeof(struct ClutTex0View) == 32) ? 1 : -1];
void func_00236068(struct ClutTex0View *clut, int block)
{
    clut->tex0.CBP = block;
    clut->tex0.PSM = clut->color_header.color_count <= 16 ? 20 : 19;
    clut->tex0.CPSM = 0;
    clut->tex0.CSM = 0;
    clut->tex0.CSA = 0;
    clut->tex0.CLD = 1;
}
