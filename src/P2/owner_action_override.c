// SLY3_CFLAGS: -Os -G0
int func_001F4F40(void *, int);
int func_001F5880(void *receiver, int selector)
{
    switch (selector) {
    case 12: return 0x204;
    case 7: return 0x266;
    case 10: return 0x267;
    case 0: return 0x268;
    }
    return func_001F4F40(receiver, selector);
}
