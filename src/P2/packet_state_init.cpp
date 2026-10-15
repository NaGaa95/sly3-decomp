// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Two original 80-byte packet defaults; field names outside address/flags remain unknown.
extern "C" char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern "C" char D_004D2D60[], D_004D2E38[], D_004D2F10[];
extern "C" int D_0036AE78, D_0036AE7C, D_0036AE80;
extern "C" int D_0036AE84, D_0036AE88, D_0036AE8C;
extern "C" void *func_0011E100(void *p, int cb, int c, int cbAlign);
struct PACKET_STATE80
{
    unsigned int address;
    unsigned int flags;
    unsigned char unknown[0x48];
};
extern "C" PACKET_STATE80 D_00475280[2];
extern "C" unsigned char D_00475340[], D_004753C0[];
extern "C" void *memset(void *p, int b, unsigned int cb);
static inline void InitPacketStateA(PACKET_STATE80 *p)
{
    PACKET_STATE80 state;
    memset(&state, 0, sizeof(state));
    state.address = (unsigned int)D_00475340 | 0x20000000;
    state.flags = 0x70000000;
    *p = state;
}
static inline void InitPacketStateB(PACKET_STATE80 *p)
{
    PACKET_STATE80 state;
    memset(&state, 0, sizeof(state));
    state.address = (unsigned int)D_004753C0 | 0x20000000;
    state.flags = 0x70002000;
    *p = state;
}
extern "C" void func_0024B940(int initialize, int priority)
{
    if (priority == 65535)
    {
        if (initialize)
        {
            PACKET_STATE80 *p = D_00475280;
            InitPacketStateA(p);
            ++p;
            InitPacketStateB(p);
            if (++D_0036AE78 == 1)
                func_0011E100(D_004D2AD8, 16, 2048, 16);
            if (++D_0036AE7C == 1)
                func_0011E100(D_004D2BB0, 24, 1024, 16);
            if (++D_0036AE80 == 1)
                func_0011E100(D_004D2C88, 24, 256, 16);
            if (++D_0036AE84 == 1)
                func_0011E100(D_004D2D60, 28, 1024, 16);
            if (++D_0036AE88 == 1)
                func_0011E100(D_004D2E38, 12, 256, 16);
            if (++D_0036AE8C == 1)
                func_0011E100(D_004D2F10, 24, 256, 16);
        }
    }
}
