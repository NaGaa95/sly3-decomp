// Compare the actual selected object clock against the receiver threshold, preserving sentinel behavior.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x14];void *object;char gap[0x70];float threshold;};
extern const float D_00326430;float func_00226458(void *receiver);
int func_00226578(struct S *p){int result=0;if(p->threshold!=D_00326430){if(func_00226458(p->object)<p->threshold)result=1;}return result;}
