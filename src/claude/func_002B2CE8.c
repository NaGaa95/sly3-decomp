// Sly 2 counterpart: _extensionAndUserData (decomp src/lib/_extensionAndUserData.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p0[0x878]; int stop; } D;
unsigned int func_002B0B78(D *d, int n);
unsigned int func_002B0C60(D *d, int n);
void func_002B2EF0(D *d, int n);
void func_002B3050(D *d);
void func_002B3058(D *d);
void func_002B2898(D *d);
void func_002B29D8(D *d);
void func_002B2AC0(D *d);
void func_002B2AD0(D *d);
void func_002B2AE0(D *d);
void func_002B2CC8(D *d);
void func_002B2CD8(D *d);
void func_002B30A8(D *d);
void func_002B3138(D *d);
void func_002B31D0(D *d);
static inline void _nextStartCode(D *d)
{
    func_002B3058(d);
    while (func_002B0C60(d, 24) != 1 && !d->stop)
        func_002B2EF0(d, 8);
}
void func_002B2CE8(D *d)
{
    void (*tbl[11])(D *) = {
        func_002B2AD0, func_002B2898, func_002B30A8, func_002B29D8, func_002B3138, func_002B2AC0, func_002B2AD0, func_002B31D0, func_002B2AE0, func_002B2CC8, func_002B2CD8,
    };
    unsigned int code;

    _nextStartCode(d);
    while ((code = func_002B0C60(d, 32)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            unsigned int id;
            func_002B3050(d);
            id = func_002B0B78(d, 4);
            id = id > 10 ? 0 : id;
            tbl[id](d);
            _nextStartCode(d);
        } else {
            func_002B3050(d);
            _nextStartCode(d);
        }
    }
}
