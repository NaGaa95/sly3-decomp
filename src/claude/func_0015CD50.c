// SLY3_CFLAGS: -Os -G0
struct VirtualEntry { short delta, reserved; void (*call)(void *, int, int, int, int, int); };
void func_001C7938(void *p);
void func_0015BEF8(void *p);

void func_0015CD50(char *p)
{
    func_001C7938(p);
    if ((unsigned)(*(int *)(p + 0x120) - 1) < 2 && *(int *)(p + 0x244)) {
        struct VirtualEntry *table;
        *(int *)(p + 0x23C) = 0;
        table = *(struct VirtualEntry **)(p + 0xC);
        table[3].call(p + table[3].delta, 9, 0, 0, 0, 0);
    }
    func_0015BEF8(p + 0x120);
}
