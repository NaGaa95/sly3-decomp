// Original USA entry 0x186fe8; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern void *D_004794CC;
void func_00189F38(void *,void *);
void func_001878E0(void *,int);
void func_00186FE8(char *p)  {
    if(D_004794CC)func_00189F38(D_004794CC,0);
    else func_00189F38(*(void **)(p+0x54),0);
    func_001878E0(p,8);
}
