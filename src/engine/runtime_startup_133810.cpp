// SLY3_CFLAGS: -Os -G0 -fno-exceptions
inline void *operator new(unsigned int size, void *where) { return where; }
struct RuntimeStartupMask {
    unsigned char bytes[16];
    RuntimeStartupMask() {}
    RuntimeStartupMask operator|(const RuntimeStartupMask &other) const {
        RuntimeStartupMask result;
        for (int i=0;i<16;++i)
            result.bytes[i]=bytes[i]|other.bytes[i];
        return result;
    }
};
extern "C" {
RuntimeStartupMask func_00252AD0(int index);
extern RuntimeStartupMask D_0036B240;
extern int D_0036AE78,D_0036AE7C,D_0036AE80;
extern int D_0036AE84,D_0036AE88,D_0036AE8C;
extern char D_004D2AD8[],D_004D2BB0[],D_004D2C88[];
extern char D_004D2D60[],D_004D2E38[],D_004D2F10[];
void *func_0011E100(void *pool,int item_bytes,int capacity,int alignment);
void func_00133810(int initialize,int priority)
{
    if(priority==65535 && initialize) {
        new (&D_0036B240) RuntimeStartupMask(func_00252AD0(47)|func_00252AD0(57)|func_00252AD0(58));
        if(++D_0036AE78==1)
            func_0011E100(D_004D2AD8,16,2048,16);
        if(++D_0036AE7C==1)
            func_0011E100(D_004D2BB0,24,1024,16);
        if(++D_0036AE80==1)
            func_0011E100(D_004D2C88,24,256,16);
        if(++D_0036AE84==1)
            func_0011E100(D_004D2D60,28,1024,16);
        if(++D_0036AE88==1)
            func_0011E100(D_004D2E38,12,256,16);
        if(++D_0036AE8C==1)
            func_0011E100(D_004D2F10,24,256,16);
    }
}
}
