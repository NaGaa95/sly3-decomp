// Clear both original state words, retain actual F12 input and store its0.001-scaled value clamped by the original range. Both range pointer A0 and float input F12 are explicit.
// Reference compiler shape: src/hand/func_001C02D0.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Range {float minimum,maximum;};
extern struct Range D_00341FF0;
struct S { char unknown_0[0x78]; int first; int second; char unknown_80[0x4]; float scaled; char unknown_88[0x18]; float value; };
float func_0011EE68(struct Range *range,float value);
void func_00283500(struct S *p,float value){p->first=0;p->second=0;p->value=value;p->scaled=func_0011EE68(&D_00341FF0,value*0.001f);}
