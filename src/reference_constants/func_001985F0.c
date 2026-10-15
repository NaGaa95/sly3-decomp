// Original USA entry 0x1985f0; ordinary C reconstruction.
// Receiver A0 and optional context pointer A1 are actual inputs. The complete 2387A8 list lookup consumes receiver+29C and property integer D3; its result pointer and context field30 are compared with the actual optional context. Existing 1985A8 explicitly declares that same pointer interface.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    char pad[0x30];
    void *context;
};
struct Record *func_002387A8(void *,int);
int func_001985F0(char *p,void *context)  {
    struct Record *r=func_002387A8(p+0x29C,0xD3);
    return r && (!context || r->context==context);
}
