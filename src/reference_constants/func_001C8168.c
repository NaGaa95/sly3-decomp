// Original USA entry 0x1c8168; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry  {
    short delta,reserved;
    void (*call)(void *,int,int,void *,void *,void *);
};
int func_001C80C0(void *);
void func_001C8168(char *p)  {
    if(func_001C80C0(p))  {
        struct VirtualEntry *v=*(struct VirtualEntry **)(p+0xC);
        v[3].call(p+v[3].delta,1,1,0,0,0);
    }
}
