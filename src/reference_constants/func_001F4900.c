// Original USA entry 0x1f4900; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_00350860[];
void *func_001C9A50(unsigned int);
void *func_002B86C8(void *);
void *func_001F4900(void *owner)  {
    char *p=func_001C9A50(0x30);
    func_002B86C8(p);
    *(void **)(p+0x20)=owner;
    *(void **)(p+0xC)=D_00350860;
    return p;
}
