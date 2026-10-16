// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0036E740[];
extern char D_0036BB88[];
void func_002A1300(int device);
void func_001A7C68(void *input, int id, int port, int slot);
void func_00164518(void *object);
void func_001A7740(void)
{
    func_002A1300(0);
    func_001A7C68(D_0036E740, 0, 0, 0);
    func_001A7C68(D_0036E740 + 0x11C0, 1, 1, 0);
    func_00164518(D_0036BB88);
}
