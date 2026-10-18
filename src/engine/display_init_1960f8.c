// SLY3_CFLAGS: -Os -G0
int func_00293380(int cause, int (*handler)(int cause), int next);
int func_00293DF8(int cause);
int func_00271B20(int initial_count, int maximum_count);
void func_00271B80(void *section);
void func_00196228(void *table, int kind);
void func_00195A98(int count, void *packet, long value);
void func_00196050(void *first, void *second);
void func_00183000(void);
int func_001953D0(int cause);
int func_00195710(int cause);
extern unsigned char D_0036E670[], D_0036DBE0[], D_0036E260[], D_0036E280[];
extern int D_0036E690, D_0036E694;
void func_001960F8(void)
{
    func_00271B80(D_0036E670);
    func_00196228(D_0036DBE0, 0);
    func_00195A98(2, D_0036E260, 1);
    func_00195A98(2, D_0036E280, 0);
    func_00196050(0, 0);
    D_0036E690 = func_00271B20(0, 1);
    D_0036E694 = func_00271B20(0, 1);
    func_00293380(2, func_001953D0, 0);
    func_00293DF8(2);
    func_00293380(0, func_00195710, 0);
    func_00293DF8(0);
    *(volatile int *)0x10003010 = 0;
    func_00183000();
}
