// SLY3_CFLAGS: -Os -G0
#include "font_affine_access.h"

void func_00265308(struct FontAffineView *font, struct FontMatrix64 *matrix,
                  const struct FontAffine32 *affine)
{
    memset(matrix, 0, sizeof(*matrix));
    {
    struct FontScreenExtent *screen = (struct FontScreenExtent *)D_0036DBE0;
    matrix->value[0] = func_002BE228((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[0] * (float)screen->width * 0.0015625f);
    matrix->value[1] = func_002BE230((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[1] * (float)screen->height * 0.0020833334f);
    matrix->value[4] = func_002BE228((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[2] * (float)screen->width * 0.0015625f);
    matrix->value[5] = func_002BE230((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[3] * (float)screen->height * 0.0020833334f);
    matrix->value[8] = func_002BE228((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[4] * (float)screen->width * 0.0015625f)
        + font->offset_x + 786432.0f;
    matrix->value[9] = func_002BE230((struct COORDINATE_CONVERSION_FIELDS *)screen,
        affine->value[5] * (float)screen->height * 0.0020833334f)
        + font->offset_y + 786432.0f;
    matrix->value[10] = 1.0f;
    matrix->value[15] = 1.0f;
    }
}
