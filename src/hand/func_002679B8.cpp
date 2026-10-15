// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Combine four decoded signed byte channels using native GNU float bounds.
#include "m2c_prelude.h"
static inline f32 ee_min(f32 left, f32 right) { return left <? right; }
static inline f32 ee_max(f32 left, f32 right) { return left >? right; }
static inline f32 clamp(f32 value) { return ee_max(ee_min(value, 1.0f), -1.0f); }
extern "C" void func_002679B8(const u8 *first_scale, const u8 *second_value,
    const u8 *second_scale, const u8 *first_value, u8 *scale_output, u8 *value_output) {
    s32 i=0;
    do {
        u8 *first_output = scale_output + i;
        f32 first = clamp((first_scale[i] - 127) * 0.007874016f);
        f32 second = clamp((second_scale[i] - 127) * 0.007874016f);
        f32 offset = 2.0f * ((f32)second_value[i] - 127.0f);
        f32 value = first * (2.0f * ((f32)first_value[i] - 127.0f));
        u8 *second_output = value_output + i;
        f32 product = first * second;
        i += 1;
        s32 encoded_value = (s32)(ee_max(ee_min((value + offset) * 0.5f, 128.0f), -127.0f) + 127.0f);
        *first_output = (s32)(clamp(product) * 127.0f + 128.0f);
        *second_output = encoded_value;
    } while (i<4);
}
