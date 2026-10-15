// Original USA entry 0x16b180; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_00355CF0[];
void *func_00169C90(void *,void *,int);
void *func_0016B180(char *p,void *owner,int mode,void *context,void *data)  {
    func_00169C90(p,owner,mode);
    *(void **)(p+0x20)=context;
    *(void **)(p+0x1C)=D_00355CF0;
    *(void **)(p+0x24)=data;
    *(int *)(p+8)=6;
    return p;
}
