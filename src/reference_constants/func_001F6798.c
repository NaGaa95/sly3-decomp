// Original USA entry 0x1f6798; ordinary C reconstruction.
// Incoming A1 is the actual optional owner passed to1FC968. That complete base initializer retainsA1 inS0 and forwards it to1FC8F8, which accesses owner+2C; therefore the source must preserve the owner formal and call argument explicitly.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry  {
    short delta,reserved;
    void (*call)(void *,int);
};
extern float D_00325520;
void func_001FC968(void *,void *);
void func_0028F068(void *,void *,int);
void func_001F6798(char *p,void *owner)  {
    struct VirtualEntry *v;
    func_001FC968(p,owner);
    v=*(struct VirtualEntry **)(p+0xC);
    v[80].call(p+v[80].delta,0);
    *(float *)(p+0x168)=D_00325520;
    func_0028F068(p,*(void **)(p+0x4C),0);
}
