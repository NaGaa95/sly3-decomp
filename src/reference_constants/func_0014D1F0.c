// Original USA entry 0x14d1f0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void func_0013CD10(void *,void *);
void func_0014D1F0(char *p,int state)  {
    if(state!=*(int *)(p+0x1E8))  {
        *(int *)(p+0x1E8)=state;
        func_0013CD10(D_00475480,p);
    }
}
