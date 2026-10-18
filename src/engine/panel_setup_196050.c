// SLY3_CFLAGS: -Os -G0
extern unsigned char D_0036E2A0[], D_0036E340[], D_0036E3D0[], D_0036E470[], D_0036E500[], D_0036E5A0[];
void func_00195C50(void *first, void *second, int count, void *table, int mode, void *colors, int color);
void func_00195B18(void);
void func_00196050(void *first, void *second)
{
    func_00195C50(first, second, 10, D_0036E2A0, 9, D_0036E340, 0);
    func_00195C50(first, second, 10, D_0036E3D0, 9, D_0036E470, 0xFFFF00);
    func_00195C50(first, second, 10, D_0036E500, 9, D_0036E5A0, 0xFF);
    func_00195B18();
}
