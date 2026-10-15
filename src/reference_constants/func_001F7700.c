// Original USA entry 0x1f7700; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry  {
    short delta,reserved;
    void (*call)(void *,int);
};
void func_001F7700(char *p,int value)  {
    if(*(int *)(p+0x130)!=1)  {
        struct VirtualEntry *v;
        *(int *)(p+0x16C)=value;
        v=*(struct VirtualEntry **)(p+0xC);
        v[80].call(p+v[80].delta,1);
    }
}
