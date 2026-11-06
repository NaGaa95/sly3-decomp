// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Start-up banner pump: builds the progress bar object, prints the version banner, then calls the 20 entries of
// the start-up function table one after another. Once the entry for func_001960F8 has been reached, the bar is
// advanced by the number of entries still to run before every call; the bar is finished and the pump ends.
// `found` and `i` are initialised after the banner/bar set-up (just before the loop): that placement is what
// makes the scheduler emit the address arithmetic of the banner call in the original order.
struct RGBA {
    unsigned char r, g, b, a;
    RGBA(unsigned int word) { *(unsigned int *)this = word; }
};
class CProg {
public:
    CProg(RGBA *p0, RGBA *p1, RGBA *p2, RGBA *p3);
private:
    unsigned char opaque[0x64];
};
typedef void (*PumpFunction)(void);
extern "C" {
extern PumpFunction D_003458D0[];
extern char D_0036BB98[];
extern char D_0034A2F8[], D_0034A2E0[];
int func_00271388(const char *format, ...);
void func_001F1430(int value);
void func_001F9550(void *prog);
void func_00165430(void *clock, int paused);
void func_001F9570(void *prog, int remaining);
void func_001F95F0(void *prog);
void func_001F15C0(int phase);
void func_001960F8(void);

void func_001CB620(void)
{
    CProg prog(&RGBA(0x807F0000), &RGBA(0x803F3F3F), &RGBA(0x80003F3F), &RGBA(0x8000003F));
    func_00271388("Sly 3: Honor Among Thieves \251 2005\n  Sony Computer Entertainment America &\n  Sucker Punch Productions\nengine: %s %s\nspaprops: %d\n\n", D_0034A2F8, D_0034A2E0, 0x205);
    func_001F1430(1);
    func_001F9550(&prog);
    int found = 0;
    unsigned int i = 0;
    do {
        func_00165430(D_0036BB98, 1);
        if (found)
            func_001F9570(&prog, 20 - i);
        else
            found = D_003458D0[i] == func_001960F8;
        D_003458D0[i]();
        i++;
    } while (i < 20);
    func_001F9570(&prog, 0);
    func_001F95F0(&prog);
    func_001F15C0(1);
}
}
