// SLY3_CFLAGS: -Os -G0
void func_0023EDC8(void *owner, void *argument);
void func_0023DEF8(void *owner, void *argument, void *slot);
void func_00206CD8(void *owner, void *argument)
{
    unsigned int i;
    func_0023EDC8(owner, argument);
    for (i = 0; i < 4; i++)
        func_0023DEF8(owner, argument, (char *)owner + i * 0x60 + 0x194);
}
