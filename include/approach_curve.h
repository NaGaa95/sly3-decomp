/* Original F12/F13/F14 and A0/A1 inputs of the scalar approach helper. */
#ifndef SLY3_APPROACH_CURVE_H
#define SLY3_APPROACH_CURVE_H
struct ApproachCurve { float initial, terminal, duration; };
typedef char Sly3ApproachCurveSize[(sizeof(struct ApproachCurve) == 12) ? 1 : -1];
#ifdef __cplusplus
extern "C" {
#endif
float func_0011E598(float input, float target, const struct ApproachCurve *curve,
                  float *derivative, float step);
#ifdef __cplusplus
}
#endif
#endif
