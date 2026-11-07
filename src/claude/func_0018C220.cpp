// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// A19/A48 drafts; A70: rewritten in the style of the matched sibling src/leaf/func_0020A200.cpp (same font/text calls).
struct Font { char data[0x84]; float dy; char pad[0x1B0 - 0x88]; };
struct Text { float x, y, dx, dy; unsigned char pad[0x10]; };
struct Chars { unsigned short a[6]; };
union Colour { unsigned int word; Chars s; };
struct Key { int id; unsigned char ch; float dx, dy; };
/* table at 0x321A38 is defined in src/claude/func_0018BB20.c (shared unit .rodata) */
extern "C" const Key D_00321A38[4];
extern unsigned short D_00344FF0[]; /* .data font string (new symbol) */
extern "C" {
void *func_00264880(Font *, const unsigned short *, float);
float func_00264EB0(Font *);
void func_00265480(Font *, Text *, int);
void func_002BC878(Text *, float, float);
void func_002BC888(Text *, float, float);
void func_002BC898(Text *, unsigned int *);
void func_002BC8B0(Text *, int);
void func_002BC8B8(Text *, int);
}
template <class T> static inline T *Addr(T *p) { return p; }
static inline void InitText(Text *tb, float x, float y, float dx, float dy, unsigned int word, Colour &u)
{
    func_002BC878(tb, x, y);
    func_002BC888(tb, dx, dy);
    unsigned int *p = Addr(&u.word);
    *p = word;
    func_002BC898(tb, p);
    func_002BC8B0(tb, 0);
    func_002BC8B8(tb, 0);
}
extern "C" void func_0018C220(int key, float x0, float y0, float gScale, float gScaleSel)
{
    Font fontSel;
    func_00264880(&fontSel, D_00344FF0, gScaleSel);
    float dxSel = func_00264EB0(&fontSel);
    float dySel = fontSel.dy;
    Font font;
    func_00264880(&font, D_00344FF0, gScale);
    float dx = func_00264EB0(&font);
    float dy = font.dy;
    Text text;
    Colour u;
    InitText(&text, 0.0f, 0.0f, 640.0f, 480.0f, 0xFF808080, u);
    Font fontT;
    unsigned int j;
    for (j = 0; j < 4; j++) {
        const Key *pk = &D_00321A38[j];
        float x = x0 + pk->dx * dx;
        float y = y0 + pk->dy * dy;
        unsigned char ch = 'o';
        float scale = gScale;
        if (pk->id == key) {
            x -= (dxSel - dx) * 0.5f;
            y -= (dySel - dy) * 0.5f;
            ch = pk->ch;
            scale = gScaleSel;
        }
        u.s.a[2] = ch;
        u.s.a[0] = '&';
        u.s.a[1] = '2';
        u.s.a[3] = '&';
        u.s.a[4] = '.';
        u.s.a[5] = 0;
        /* zero-insn no-op asms (A70): extra refs give x f20 / y f21 and let the text stores issue first */
        __asm__("" : "=f"(x) : "0"(x));
        __asm__("" : "=f"(y) : "0"(y));
        func_00264880(&fontT, u.s.a, scale);
        text.x = x;
        text.y = y;
        func_00265480(&fontT, &text, 0x1A);
    }
}
