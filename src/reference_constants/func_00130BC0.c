// Original USA entry 0x130bc0; ordinary C reconstruction.
// Receiver A0 and owner/value A1 are retained. EmptyD0 allocates through169BF8(size24), whose fixed-pool allocation ignores the size.130CD0 receives actual storage A0/owner A1/order13 A2/receiver A3, forwarding its first three inputs into169C90 and storing the fourth at20. Returned storage is installed before169CE0, which consumes only that storage and performs list registration.
// SLY3_CFLAGS: -Os -G0
void *func_00169BF8(unsigned int);
void *func_00130CD0(void *,void *,int,void *);
void func_00169CE0(void *);
void func_00130BC0(char *p,void *value)  {
    if(!*(void **)(p+0xD0)) {
        *(void **)(p+0xD0)=func_00130CD0(func_00169BF8(0x24),value,13,p);
        func_00169CE0(*(void **)(p+0xD0));
    }
}
