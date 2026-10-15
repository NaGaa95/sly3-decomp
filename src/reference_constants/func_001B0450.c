// Original USA entry 0x1b0450; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VirtualEntry  {
    short delta,reserved;
    void (*call)(void *,qword);
};
qword func_0011FD70(float,float,float);
void func_001B0450(char *p)  {
    qword value=func_0011FD70(*(float *)(p+0x1BC),1000.0f,0.0f);
    struct VirtualEntry *v=*(struct VirtualEntry **)(p+0xC);
    v[40].call(p+v[40].delta,value);
}
