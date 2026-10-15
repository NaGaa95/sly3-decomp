// Original USA entry 0x1d5540; ordinary C reconstruction.
// Optional receiver A0 is retained.1854C8 receives global36C700/kind3C/nullcontext explicitly;187040 receives original4794C4 object and builds all subsequent object/flag/scalar arguments internally. Nonnull receiver flags1C acquire bit1. No original FP or other GP input is consumed.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
extern void *D_004794C4;
void func_001854C8(void *,int,void *);
void func_00187040(void *);
void func_001D5540(char *p)  {
    func_001854C8(D_0036C700,0x3C,0);
    func_00187040(D_004794C4);
    if(p)*(unsigned int *)(p+0x1C)|=2;
}
