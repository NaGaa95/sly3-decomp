// Original USA entry 0x173950; ordinary C reconstruction.
// Receiver A0 only. Original owner14.delta50 must satisfy ordered0<=delta and elapsed4C+delta<clock36BB98 before1739A8(receiver). Complete1739A8 and173A98 derive their own object/list/message inputs and do not consume an original incoming FPR or second GP argument.
// SLY3_CFLAGS: -Os -G0
extern float D_0036BB98;
void func_001739A8(void *);
void func_00173950(char *p)  {
    float delta=*(float *)(*(char **)(p+0x14)+0x50);
    if(0.0f<=delta && *(float *)(p+0x4C)+delta<D_0036BB98)func_001739A8(p);
}
