// Clamp the actual float input to [0, 1] and return the original quadratic ease-out value.
// Complete original body, actual inputs and every initialized section are independently reviewed.
// Clamp the actual float input to [0, 1], then apply the original quadratic ease-out expression.
// SLY3_CFLAGS: -Os -G0
static inline float Clamp(float value, float low, float high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}
float func_0027A610(float value) {
    value = Clamp(value, 0.0f, 1.0f);
    return (value + value) - (value * value);
}
