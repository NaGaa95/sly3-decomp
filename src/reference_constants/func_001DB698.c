// Original USA entry 0x1db698; ordinary C reconstruction.
// MPEG callback registration at1DC280 passes this address to slot4 of2AA050. Dispatch forwards the registered context asA2; decoder/event parameters are unused by this callback.
// SLY3_CFLAGS: -Os -G0
void func_001DC430(void *,int);
void func_001DB490(void *);
int func_001DB698(void *unused0,void *unused1,char *p)  {
    func_001DC430(p,0);
    func_001DB490(p+0x180);
    return 1;
}
