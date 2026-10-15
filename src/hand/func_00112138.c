// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Allocate the original object size and invoke its Sly 3 constructor.
// Sly 2 factory reference: src/hand/func_001112A8.cpp.
void *func_001D27F0(unsigned int size);
void *func_002B5AE0(void *storage);
void *func_00112138(void)
{
    void *storage = func_001D27F0(0x1A0);
    return func_002B5AE0(storage);
}
