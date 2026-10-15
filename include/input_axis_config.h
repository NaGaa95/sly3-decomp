#ifndef SLY3_INPUT_AXIS_CONFIG_H
#define SLY3_INPUT_AXIS_CONFIG_H

// The original getter advances by 16 bytes. The complete axis consumer
// reads whole-word inversion flags at 0/4 and float scales at 8/12.
// The original array length and class name remain unknown.
struct INPUT_AXIS_CONFIG {
    int invertX;
    int invertY;
    float scaleX;
    float scaleY;
};

#ifdef __cplusplus
extern "C" {
#endif
extern struct INPUT_AXIS_CONFIG D_00345098[];
struct INPUT_AXIS_CONFIG *func_001A7B20(int index);
#ifdef __cplusplus
}
#endif

#endif
