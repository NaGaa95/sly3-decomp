// SLY3_CFLAGS: -Os -G0 -ffast-math
// Boot-time load of the startup overlay table: initialise the device, optionally wait for the media check, then DMA every
// table entry to its destination in chunks and run its callback (same routine as Sly 2 func_001A7630).
struct Entry { int bytes; unsigned int source; int argumentBytes; const char *arguments; int x10; int x14; };
struct Dma { unsigned int source; unsigned int destination; int bytes; int attributes; };
extern struct Entry *D_00566EC0;
extern struct Entry *D_00566F9C;
extern int D_00370CC8;
extern char D_00323890[];
void func_002956E0(int n);
void func_00297B80(void);
void func_002A06E8(int n);
int func_00162E08(void);
void func_00162E48(void);
void func_00296AF0(void);
void func_00162FF0(char *p, char *s, int n);
int func_00297FC0(const char *p);
int func_00297F70(void);
void func_002A0BE8(int n);
int func_00163150(int n);
int func_00297850(void);
void *func_002978D8(int cb);
void func_00293920(int n);
int func_00293A60(struct Dma *p, int n);
int func_00297DC0(void *h, int argumentBytes, const char *arguments);
int func_002979C0(void *h);
void func_001CB2D8(void)
{
    union { char buf[0x100]; struct Dma dma; } u;
    struct Entry *pe;
    int cbMax;
    void *h;
    func_002956E0(0);
    func_00297B80();
    func_002A06E8(0);
    if (!func_00162E08())
        while (1)
            ;
    func_00162E48();
    func_00296AF0();
    if (!D_00370CC8) {
        func_00162FF0(u.buf, D_00323890, 1);
        while (!func_00297FC0(u.buf))
            ;
        while (!func_00297F70())
            ;
        func_002956E0(0);
        func_00297B80();
        func_002A06E8(0);
        if (!func_00162E08())
            while (1)
                ;
        func_00162E48();
        func_00296AF0();
    }
    func_002A0BE8(0);
    func_00163150(1);
    func_00297850();
    cbMax = 0;
    {
        struct Entry *p = D_00566EC0;
        struct Entry *end = D_00566F9C;
        for (; p < end; p++)
            if (p->bytes >= cbMax)
                cbMax = p->bytes;
    }
    h = func_002978D8(cbMax);
    for (pe = D_00566EC0; pe < D_00566F9C; pe++) {
        int cb = pe->bytes;
        int off = 0;
        while (cb) {
            int limit = 0xFFFC0;
            int c;
            if (cb >= limit)
                c = limit;
            else
                c = cb;
            u.dma.source = pe->source + off;
            u.dma.destination = (unsigned int)h + off;
            u.dma.bytes = c;
            u.dma.attributes = 0;
            func_00293920(0);
            while (!func_00293A60(&u.dma, 1))
                ;
            cb -= c;
            off += c;
        }
        {
            int r;
            do {
                r = func_00297DC0(h, pe->argumentBytes, pe->arguments);
            } while (r < 0 && r != pe->x14);
        }
    }
    func_002979C0(h);
}
