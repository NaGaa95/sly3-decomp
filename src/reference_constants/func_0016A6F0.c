// Original USA entry 0x16a6f0; ordinary C reconstruction.
// Original constructor receiver A0, owner A1 and signed32-bit order A2 are explicit.169C90 stores actual owner at0/order at4 and returns receiver; all three inputs are forwarded even though the outer prologue only retains A0. The concrete355D18 table, type4, floats7/-1 and zero D0/D4 are installed before the original receiver pointer return. No fake receiver-only base interface is used.
// SLY3_CFLAGS: -Os -G0
extern char D_00355D18[];
void func_00169C90(void *,void *,int);
void *func_0016A6F0(char *p,void *owner,int order)  {
    func_00169C90(p,owner,order);
    *(void **)(p+0x1C)=D_00355D18;
    *(int *)(p+8)=4;
    *(float *)(p+0xC4)=7.0f;
    *(float *)(p+0x28)=-1.0f;
    *(int *)(p+0xD0)=0;
    *(int *)(p+0xD4)=0;
    return p;
}
