// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Same physical wrapper protocol as the existing complete 0x001FD988 factory.
extern unsigned char D_003505D0[];
void *func_001C9A50(unsigned int);
void *func_002B8808(void *);

void *func_001FDF70(void *owner)
{
    char *wrapper = func_001C9A50(0x30);
    func_002B8808(wrapper);
    *(void **)(wrapper + 0x20) = owner;
    *(void **)(wrapper + 0xC) = D_003505D0;
    return wrapper;
}
