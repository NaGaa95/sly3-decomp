// Original USA entry 0x1bd6c8; ordinary C reconstruction.
// Only record receiver A0 is consumed. State1C selects 1B7268(scale F12=1, record A0, action A1=3, resource A2=null, context A3=null), or 1B77F8(record A0, action A1=6, context A2=null). Full first callee retains exactly F12 and A0/A1/A2/A3. Floating argument position agrees with the existing 22D318 declaration.
// SLY3_CFLAGS: -Os -G0
void func_001B7268(float,void *,int,void *,void *);
void func_001B77F8(void *,int,void *);
void func_001BD6C8(char *p)  {
    if(*(int *)(p+0x1C)==18)func_001B7268(1.0f,p,3,0,0);
    else func_001B77F8(p,6,0);
}
