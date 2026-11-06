// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Static initializer of this unit (g++ __static_initialization_and_destruction form): an empty class-id set, the
// set of class ids used by this unit, and the shared slot pools (one counter each, as in func_00133810).
inline void *operator new(unsigned int size, void *where) { return where; }
struct Mask {
    unsigned char bytes[16];
    Mask() {}
    Mask operator|(const Mask &other) const {
        Mask result;
        for (int i = 0; i < 16; ++i)
            result.bytes[i] = bytes[i] | other.bytes[i];
        return result;
    }
};
extern "C" {
Mask func_00252AD0(int index);
void *memset(void *, int, unsigned int);
extern Mask D_00475440, D_00475450, D_00475460;
extern int D_0036AE78, D_0036AE7C, D_0036AE80;
extern int D_0036AE84, D_0036AE88, D_0036AE8C;
extern char D_004D2AD8[], D_004D2BB0[], D_004D2C88[];
extern char D_004D2D60[], D_004D2E38[], D_004D2F10[];
void *func_0011E100(void *pool, int item_bytes, int capacity, int alignment);
void func_00258010(int initialize, int priority)
{
    if (priority == 65535 && initialize) {
        memset(&D_00475440, 0, sizeof(Mask));
        new (&D_00475450) Mask(func_00252AD0(5)|func_00252AD0(6)|func_00252AD0(42)|func_00252AD0(7)|func_00252AD0(35)|func_00252AD0(1)|func_00252AD0(41)|func_00252AD0(59)|func_00252AD0(65));
        new (&D_00475460) Mask(func_00252AD0(17)|func_00252AD0(49)|func_00252AD0(7)|func_00252AD0(5)|func_00252AD0(6)|func_00252AD0(35)|func_00252AD0(1)|func_00252AD0(41)|func_00252AD0(59)|func_00252AD0(68)|func_00252AD0(33)|func_00252AD0(34));
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
