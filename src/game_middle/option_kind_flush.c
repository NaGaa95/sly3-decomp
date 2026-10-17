// SLY3_CFLAGS: -Os -G0
extern char D_00468D30[];
void func_0021D360(void *buffer);
void func_0021D4C8(void *buffer);
void func_001D2ED0(void *owner, int mode);
void func_001D4498(void *owner, int *kind)
{
    switch (*kind) {
    case 0x5C: case 0x5D: case 0x5E: case 0x5F: case 0x60: case 0x77: case 0x78:
        func_0021D360(D_00468D30);
        break;
    case 0x4E:
        func_0021D4C8(D_00468D30);
        break;
    }
    func_001D2ED0(owner, 9);
}
