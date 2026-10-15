// Original USA entry 0x1fd758; complete ordinary C body.
// Actual storage, owner pointer and stream word are forwarded into the base.
// The allocated48-byte buffer receives the original initialized record.
// SLY3_CFLAGS: -Os -G0
struct Descriptor  {
    int bytes,alignment;
};
extern char D_00361490[],D_00347EF0[];
void *func_001FCCE8(void *,void *,int);
void *func_001D24D0(const struct Descriptor *,const char *);
void *func_001FD758(char *p,void *owner,int value)  {
    struct Descriptor descriptor;
    func_001FCCE8(p,owner,value);
    *(void **)(p+0x18)=D_00361490;
    descriptor.alignment=16;
    descriptor.bytes=48;
    *(void **)(p+0x1C)=func_001D24D0(&descriptor,D_00347EF0);
    return p;
}
