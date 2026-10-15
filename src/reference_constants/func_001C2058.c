// Original USA entry 0x1c2058; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
struct Record  {
    char storage[16];
};
void func_001C2138(void *,struct Record *);
void func_001C2058(char *p)  {
    int remaining;
    struct Record *record=(struct Record *)(p+0x2C);
    for(remaining=13;remaining>=0;--remaining)  {
        func_001C2138(p,record);
        ++record;
    }
}
