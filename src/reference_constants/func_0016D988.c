// Original USA entry 0x16d988; ordinary C reconstruction.
// Only receiver A0 is consumed. Full131598 begins with empty238978 and derives all later arguments from receiver fields.256828 explicitly takes owner10 A0/null A1/null A2/full128-bit vector317560 A3; no inherited FPR is read.256DF0,259D10(owner10+4B0),16E118(receiver,0),2389C0(receiver) derive their own downstream inputs.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern qword D_00317560;
void func_00131598(void *);
void func_00256828(void *,int,int,qword);
void func_00256DF0(void *);
void func_00259D10(void *);
void func_0016E118(void *,int);
void func_002389C0(void *);
void func_0016D988(char *p)  {
    func_00131598(p);
    func_00256828(*(void **)(p+0x10),0,0,D_00317560);
    func_00256DF0(*(void **)(p+0x10));
    func_00259D10(*(char **)(p+0x10)+0x4B0);
    func_0016E118(p,0);
    func_002389C0(p);
}
