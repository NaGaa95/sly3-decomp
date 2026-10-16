// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

int func_002980D0(void);
int func_00298EA8(void);
int func_00298120(void);

int func_00298F18(void)
{
    int enabled = func_002980D0();
    int result = func_00298EA8();
    if (enabled) {
        func_00298120();
    }
    return result;
}
