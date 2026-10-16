// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

typedef unsigned long TimerTime64;
typedef char timer_time_is64[(sizeof(TimerTime64) == 8) ? 1 : -1];

int func_002980D0(void);
int func_00298120(void);
void func_00298740(unsigned int mode);
TimerTime64 func_00298E50(void);
void func_00298958(TimerTime64 now);

int func_002988C0(void)
{
    int enabled = func_002980D0();
    unsigned int mode = *(volatile unsigned int *)0x10001010;

    if (mode & 0x80) {
        if (enabled) {
            func_00298120();
        }
        return 1;
    }

    func_00298740((mode & 0xFFFFF3FFU) | 0x80);
    func_00298958(func_00298E50());
    if (enabled) {
        func_00298120();
    }
    return 0;
}
