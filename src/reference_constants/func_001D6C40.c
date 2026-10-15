// Original USA entry 0x1d6c40; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
void func_0023BBE0(void *);
void func_00137588(int,void *,int,void *,float,float);
void func_001309D8(void *);
void func_001D6D20(void *,int);
void func_001D6C40(char *p)  {
    func_0023BBE0(p);
    func_00137588(0,p,0,p+0x214,0.0f,1.0f);
    func_001309D8(p+0x248);
    func_001D6D20(p,0);
}
