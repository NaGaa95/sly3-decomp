// Original USA entry 0x1d7738; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_00252E40(void *,int);
void func_00238978(void *);
void func_001D77E0(void *,int,void *);
void func_001D7D10(void *);
void func_001D7738(char *p)  {
    if(*(int *)(p+0x38)!=-1)func_00252E40(*(void **)(p+0x10),*(int *)(p+0x38));
    func_00238978(p);
    func_001D77E0(p,4,0);
    func_001D7D10(p);
}
