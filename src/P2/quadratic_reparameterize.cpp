// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Compose c + l*t + q*t*t with t = scale*u + offset.
// Keep the three original stores/reloads, including in-place alias behavior.
struct QuadraticCoefficients { float constant, linear, quadratic; };
extern "C" void func_0011EAD0(QuadraticCoefficients *source, QuadraticCoefficients *output, float scale, float offset)
{
    output->quadratic = source->quadratic * scale * scale;
    output->linear = (source->quadratic + source->quadratic) * scale * offset + source->linear * scale;
    output->constant = source->quadratic * offset * offset + source->linear * offset + source->constant;
}
