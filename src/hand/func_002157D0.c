// Store both explicit integer controls after clamping each to its original upper bound.
// Reference algorithm: src/hand/func_00120370.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x190]; int first; int second; int first_limit; int second_limit; };
static inline int Minimum(int value,int limit){return value<limit?value:limit;}
void func_002157D0(struct S *p,int first,int second){p->first=Minimum(first,p->first_limit);p->second=Minimum(second,p->second_limit);}
