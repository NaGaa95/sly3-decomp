// Sly 2 counterpart: _sceMpegDispatchMpegCbNodata (decomp src/lib/_sceMpegDispatchMpegCbNodata.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int type; int pad[7]; } sceMpegCbData;
typedef int (*sceMpegCallback)(void *mp, sceMpegCbData *cbd, void *data);
typedef struct { sceMpegCallback func; void *data; void *gp; } CB;
typedef struct { char p0[0x40]; CB *cb; } sceMpeg;
static inline void *SetGp(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $28\n\tmove $28, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
int func_002AA110(sceMpeg *mp)
{
    sceMpegCbData cbd;
    CB *t;
    sceMpegCallback f;
    cbd.type = 1;
    if (mp && (t = mp->cb) && (f = (t + cbd.type)[1].func)) {
        void *old = SetGp(((void **)(t + cbd.type))[5]);
        f(mp, &cbd, (t + cbd.type)[1].data);
        SetGp(old);
    }
    return 1;
}
