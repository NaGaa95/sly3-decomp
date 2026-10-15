// Original USA entry 0x173228; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry  {
    short delta,reserved;
    void (*call)(void *,int);
};
void func_00173228(char *p)  {
    char *object=*(char **)(p+0x4C);
    struct VirtualEntry *v=*(struct VirtualEntry **)(object+0xC);
    v[99].call(object+v[99].delta,-1);
    object=*(char **)(p+0x4C);
    v=*(struct VirtualEntry **)(object+0xC);
    v[99].call(object+v[99].delta,0);
}
