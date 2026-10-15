// Original USA entry 0x155d00; ordinary C reconstruction.
// Only receiver A0 is consumed. Optional owner11B4 and13B500(owner,selector3A) gate explicit2387A8(owner+29C,selectorDA), returning the real record pointer. Its owner5C must equal receiver before state60 is cleared.13B500 keeps the selector itself across receiver-derived script lookup and13BEC8, which takes exactly returned script kind and selector.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    char pad[0x5C];
    void *owner;
    int state;
};
int func_0013B500(void *,int);
struct Record *func_002387A8(void *,int);
void func_00155D00(char *p)  {
    struct Record *r;
    if(*(void **)(p+0x11B4) && func_0013B500(*(void **)(p+0x11B4),0x3A)) {
        r=func_002387A8(*(char **)(p+0x11B4)+0x29C,0xDA);
        if(r && r->owner==p)r->state=0;
    }
}
