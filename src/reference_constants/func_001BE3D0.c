// Reference algorithm: src/hand/func_00146EE0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001BE4A8(void *p);
void func_001BE408(void *p);
void func_001BE3D0(char *p)
{
    void *previous; func_001BE4A8(p);
    previous = *(void **)(p + 0xA0);
    *(void **)(p + 0xA0) = 0;
    *(void **)(p + 0x40) = previous;
    func_001BE408(p);
}
