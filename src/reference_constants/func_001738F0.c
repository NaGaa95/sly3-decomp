// Original USA entry 0x1738f0; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_00479C10[];
void func_002BAA50(void *,void *);
void func_002BBF40(void *,void *);
void func_0013BDE0(void *);
void func_0011E1F0(void *,void *);
void func_001738F0(char *p)  {
    if(--*(int *)(p+0x10)<=0)  {
        func_002BAA50(p,0);
        func_002BBF40(p+4,0);
        func_0013BDE0(p);
        func_0011E1F0(D_00479C10,p);
    }
}
