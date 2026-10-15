// Original USA entry 0x19b4c0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void func_0023BAB8(void *);
void func_0019F5D8(void *,void *);
static inline int IsNonzero(float value)  {
    return value!=0.0f;
}
void func_0019B4C0(char *p)  {
    func_0023BAB8(p);
    if(IsNonzero(*(float *)(p+0x1D4)))func_0019F5D8(D_00475480,p);
}
