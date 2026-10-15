// Original USA entry 0x1fb528; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Key  {
    short first,second;
    union  {
        short s;
        int i;
    } value;
};
extern struct Key D_003255A0;
extern char D_00475480[];
void func_001C85E8(void *);
void func_0015DCD0(void *,void *,struct Key,int);
void func_001FB528(char *p)  {
    func_001C85E8(p);
    if(*(int *)(p+0xD4)==1)func_0015DCD0(D_00475480,p,D_003255A0,0);
}
