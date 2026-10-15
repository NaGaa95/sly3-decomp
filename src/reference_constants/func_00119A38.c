// Original USA entry 0x119a38; ordinary C reconstruction.
// Original destructor receiver A0 and flags A1 are explicit. Its table pointer at30 is installed before flags bit0 selects 1D2818(receiver). No preserved register is used as an unexpressed input.
// SLY3_CFLAGS: -Os -G0
extern char D_00350ED0[];
void func_001D2818(void *);
void func_00119A38(char *p,int flags)  {
    *(void **)(p+0x30)=D_00350ED0;
    if(flags&1)func_001D2818(p);
}
