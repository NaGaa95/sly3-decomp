// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Allocate the original object size and invoke its Sly 3 constructor.
// Sly 2 factory reference: src/hand/func_00111EF0.cpp.
void *func_001D27F0(unsigned int size);
void *func_002B75F0(void *storage);
void *func_00112AC0(void)
{
    void *storage = func_001D27F0(0x280);
    return func_002B75F0(storage);
}
