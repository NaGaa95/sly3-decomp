// Select the original clock through its inline-or-pointer tagged state.
// Receiver-only API and complete original entry/boundary independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x3C];unsigned int state;};
extern float D_0036BB98,D_0036BBD8;
float func_00226458(struct S *p){unsigned int flags=p->state;if((flags^1)&1)flags=*(const unsigned int *)flags;if(flags&0x200)return D_0036BBD8;return D_0036BB98;}
