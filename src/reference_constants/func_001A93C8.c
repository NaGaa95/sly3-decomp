// Original USA entry 0x1a93c8; ordinary C reconstruction.
// Unused historical receiver A0, selection A1 and flags A2 are explicit. Selection!=1 updates player0; selection!=0 updates player1 at the proved11C0 stride. Complete1A9630 consumes only explicit player A0/flags A1, increments original counters and constructs its own downstream event inputs.
// SLY3_CFLAGS: -Os -G0
extern char D_0036E740[];
void func_001A9630(void *,unsigned int);
void func_001A93C8(void *unused,int selection,unsigned int flags)  {
    if(selection!=1)func_001A9630(D_0036E740,flags);
    if(selection!=0)func_001A9630(D_0036E740+0x11C0,flags);
}
