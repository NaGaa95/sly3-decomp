// Original USA entry 0x189da0; ordinary C reconstruction.
// Original receiver A0/value A1 are explicit. Complete1880F0 reads only receiver40/FC and consumes no second or floating input. On true, the real local value and pointer-to-value are passed through adjusted standard message slot3 as selector1A/null/flag1/pointer-to-pointer/null, with all six observed GP arguments explicit. Nominal callback class remains provisional.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
struct VirtualEntry  {
    short delta,pad;
    void (*call)(void *,int,void *,int,int **,void *);
};
int func_001880F0(void *);
void func_00189DA0(char *p,int value)  {
    if(func_001880F0(p)) {
        int *address=&value;
        struct VirtualEntry *v=*(struct VirtualEntry **)(p+0xC);
        v[3].call(p+v[3].delta,0x1A,0,1,&address,0);
    }
}
