// Clamp the actual incoming float ratio F12/F13 through the original two-float range, then submit the explicit receiver/identifier and returned F12 value. No range address is modeled as an integer or hidden argument.
// Reference compiler shape: src/hand/func_001AC850.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Range {float minimum,maximum;};
extern struct Range D_00341FF0;
float func_0011EE68(struct Range *range,float value);
void func_00261580(void *receiver,int identifier,float value);
void func_00261528(void *receiver,int identifier,float numerator,float denominator){func_00261580(receiver,identifier,func_0011EE68(&D_00341FF0,numerator/denominator));}
