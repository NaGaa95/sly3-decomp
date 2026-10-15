// Reference: Sly 2 src/lib/_sceMpegError.c; target Sly 3 0x002AE460.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
typedef struct { int type; const char *message; } CBERR;
typedef struct { char pad[0xC]; int cb; } CBS;
typedef struct { char pad[0x868]; void *mp; } DEC;
int _sceMpegDispatchMpegCallback(void *, void *);
void func_002AE2E8(const char *);
void _sceMpegError(DEC *d, const char *message)
{
    void *mp = d->mp;
    if (mp && d && ((CBS *)d)->cb) {
        CBERR e;
        e.message = message;
        e.type = 0;
        _sceMpegDispatchMpegCallback(mp, &e);
    } else {
        func_002AE2E8(message);
    }
}
