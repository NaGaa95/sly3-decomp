#ifndef SLY3_PRIVATE_FONT_AFFINE_ACCESS_H
#define SLY3_PRIVATE_FONT_AFFINE_ACCESS_H

struct FontAffineView {
    unsigned char opaque00[0x64];
    float offset_x, offset_y;
    float x, y, width, height;
    float scale_x, scale_y, baseline, scale;
    unsigned char opaque8C[0x198 - 0x8C];
    int vertical_alignment;
    int horizontal_alignment;
    int layer;
};
struct FontAffine32 { float value[8]; } __attribute__((aligned(16)));
struct FontMatrix64 { float value[16]; } __attribute__((aligned(16)));
struct COORDINATE_CONVERSION_FIELDS;
struct FontScreenExtent { int mode, width, height; };

typedef char FontAffineSize32[sizeof(struct FontAffine32) == 32 ? 1 : -1];
typedef char FontMatrixSize64[sizeof(struct FontMatrix64) == 64 ? 1 : -1];
typedef char FontViewSize1A4[sizeof(struct FontAffineView) == 0x1A4 ? 1 : -1];

extern unsigned char D_0036DBE0[];
float func_002BE228(struct COORDINATE_CONVERSION_FIELDS *, float);
float func_002BE230(struct COORDINATE_CONVERSION_FIELDS *, float);
void *memset(void *, int, unsigned int);
void func_00265308(struct FontAffineView *, struct FontMatrix64 *, const struct FontAffine32 *);
void func_002655C0(struct FontAffineView *, const struct FontAffine32 *, void *);
void func_00265660(struct FontAffineView *, struct FontMatrix64 *, void *);

#endif
