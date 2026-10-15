// Original USA entry 0x154ba8; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_00154B48(void *,int);
void func_002091B0(void *,void *);
void func_002093E8(void *);
void func_00154BA8(char *p,void *value)  {
    func_00154B48(p,0);
    if(value)func_002091B0(p+0x940,value);
    else func_002093E8(p+0x940);
}
