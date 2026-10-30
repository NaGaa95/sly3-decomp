// SLY3_CFLAGS: -Os -G0
struct G { unsigned short ch; short pad; int x4; };
struct F { char pad[0x138]; int c; struct G *ag; };
struct G *func_001812B0(struct F *p, unsigned short ch)
{
    int lo = 0;
    int hi = p->c - 1;
    if (ch == 0xA0)
        ch = 0x20;
    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        int d = ch - p->ag[mid].ch;
        if (d == 0)
            return &p->ag[mid];
        if (d > 0)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return 0;

}
