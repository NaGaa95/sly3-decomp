// SLY3_CFLAGS: -Os -G0
unsigned int func_00139A40(unsigned int flags)
{
    if (!(flags & 0x3)) flags |= 0x3;
    if (!(flags & 0xC)) flags |= 0xC;
    if (!(flags & 0xF0)) flags |= 0xF0;
    if (!(flags & 0x1F00)) flags |= 0x1F00;
    if (!(flags & 0x30000)) flags |= 0x30000;
    if (!(flags & 0x300000)) flags |= 0x300000;
    return flags;
}
