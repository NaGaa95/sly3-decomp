// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

typedef unsigned long TimerInterval64;
typedef char timer_interval_is64[(sizeof(TimerInterval64) == 8) ? 1 : -1];
typedef char timer_handle_is32[(sizeof(int) == 4) ? 1 : -1];
typedef char timer_pointer_is32[(sizeof(void *) == 4) ? 1 : -1];

int func_002980D0(void);
int func_00298120(void);
int func_002990A0(int handle, TimerInterval64 interval,
                  void *callback_address, void *context);

int func_00299198(int handle, TimerInterval64 interval,
                  void *callback_address, void *context)
{
    int enabled = func_002980D0();
    int result = func_002990A0(handle, interval, callback_address, context);
    if (enabled) {
        func_00298120();
    }
    return result;
}
