// Original USA entry 0x141f80; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct VirtualEntry  {
    short delta,reserved;
    void *(*query)(void *);
};
void func_00141FD8(void *,void *);
void func_00141F80(char *p)  {
    if(!*(int *)(p+0x198))  {
        char *object=*(char **)(p+0x434);
        if(object)  {
            struct VirtualEntry *v=*(struct VirtualEntry **)object;
            func_00141FD8(p,v[1].query(object+v[1].delta));
        }
    }
}
