// Original USA entry 0x15cce8; ordinary C reconstruction.
// Only receiver A0 is consumed.1C7DC8 and its1C7F18 callback loop derive remaining arguments from receiver;15BE30 receives embedded receiver120. Nonzero244 uses a real eight-byte allocation descriptor with bytes256/alignment16, passing its pointer to complete1D2470.2407D8 reads embedded E0 array/count and produces its own floating result stored210;15D100 receives only receiver and defines every downstream input.
// SLY3_CFLAGS: -Os -G0
struct Allocation  {
    unsigned int bytes,alignment;
};
void func_001C7DC8(void *);
void func_0015BE30(void *);
void *func_001D2470(const struct Allocation *);
float func_002407D8(void *);
void func_0015D100(void *);
void func_0015CCE8(char *p)  {
    func_001C7DC8(p);
    func_0015BE30(p+0x120);
    if(*(int *)(p+0x244)) {
        struct Allocation request;
        request.bytes=256;
        request.alignment=16;
        *(void **)(p+0x240)=func_001D2470(&request);
    }
    *(float *)(p+0x210)=func_002407D8(p+0xE0);
    func_0015D100(p);
}
