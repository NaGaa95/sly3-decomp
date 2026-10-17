// SLY3_CFLAGS: -Os -G0
struct Global { unsigned char prefix[0x40]; int word40; unsigned char gap44[4]; int word48; unsigned char gap4C[0xC]; int word58; };
struct Record { unsigned char prefix[0x1C]; int text1C; int text20; int text24; unsigned char rest[0x3C - 0x28]; };
struct Entry { int id; int a[7]; };
extern struct Global D_0046F7A0;
extern struct Record D_00343098[];
extern const char *D_00349050[];
extern char D_003260A8[];
extern char D_003260B0[];
extern char D_003260B8[];
extern unsigned char D_00475480[];
const unsigned short *func_00150630(void *pool, int id);
struct Entry *func_0021F310(struct Global *global, int id);
void *func_001F4AD0(void *pool, int index);
int func_00154758(void *context, int id);
unsigned short *func_00271730(unsigned short *destination, const unsigned short *source);
unsigned short *func_00271780(unsigned short *destination, const unsigned short *source);
unsigned short *func_00271828(unsigned short *destination, const char *text);
int func_002715B0(unsigned short *output, const unsigned short *format, ...);
void func_002207E8(unsigned short *destination)
{
    unsigned short buffer[0x100];
    if (D_0046F7A0.word40 != -1) {
        func_00271730(destination, func_00150630(D_00475480, D_0046F7A0.word48));
        return;
    }
    if (D_0046F7A0.word58 != -1)
        goto composed;
    func_00271730(destination, func_00150630(D_00475480, 0x132));
    return;
composed:
    {
        const void *extra = 0;
        struct Entry *entry = func_0021F310(&D_0046F7A0, D_0046F7A0.word58);
        int index = func_00154758(func_001F4AD0(D_00475480, 0), D_0046F7A0.word58);
        if ((entry->a[6] & 1) && index < 0) {
            func_00271730(buffer, func_00150630(D_00475480, 0x136));
        } else {
            extra = index >= 0 ? D_00349050[index] : D_003260A8;
            func_002715B0(buffer, func_00150630(D_00475480, D_00343098[D_0046F7A0.word58].text24), extra, extra, extra);
            extra = func_00150630(D_00475480, D_00343098[D_0046F7A0.word58].text20);
        }
        func_00271730(destination, func_00150630(D_00475480, D_00343098[D_0046F7A0.word58].text1C));
        if (extra) {
            func_00271828(destination, D_003260B0);
            func_00271780(destination, extra);
        }
        func_00271828(destination, D_003260B8);
        func_00271780(destination, buffer);
    }
}
