// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Font { char data[0x84]; float dy; char pad[0x1B0 - 0x88]; };
struct Text { float x, y, dx, dy; unsigned char pad[0x10]; };
struct Chars { unsigned short a[6]; };
union Colour { unsigned int word; Chars s; };
struct Key { int id; unsigned char ch; float dx, dy; };
struct Entry { float t; int k; char pad8[8]; qword pos; int done; char pad24[0x30 - 0x24]; };
struct Prompt {
    char pad0[0x190]; int state; char pad194[0x19C - 0x194]; float dt; int count; char pad1A4[0x1B0 - 0x1A4];
    Entry entries[6]; char pad2D0[0x390 - 0x2D0]; int hintState; int hintIndex; char pad398[0x3A0 - 0x398];
    qword pos; qword vel;
};
struct Clock { float time, dt; };
extern Clock D_0036BB98;
extern char D_00474FF0[];
extern unsigned short D_00347FC0[], D_00347FD0[], D_00347FE0[];
extern Key D_003258C0[4];
extern qword D_00325900, D_00325910;
extern "C" {
void func_0023CC40(Prompt *);
float func_002483D8(void *);
void *func_00264880(Font *, const unsigned short *, float);
float func_00264EB0(Font *);
void func_00265480(Font *, Text *, int);
void func_002BC878(Text *, float, float);
void func_002BC888(Text *, float, float);
void func_002BC898(Text *, unsigned int *);
void func_002BC8B0(Text *, int);
void func_002BC8B8(Text *, int);
void func_00118558(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
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
static inline float GMax(float a, float b) { return a < b ? b : a; }
extern "C" void func_0020A200(Prompt *p)
{
    func_0023CC40(p);
    float t = func_002483D8(D_00474FF0);
    if (p->state < 3) if (p->state > 0) if (p->count != 0) {
        Font fontA;
        func_00264880(&fontA, D_00347FC0, 1.2f);
        Font fontB;
        func_00264880(&fontB, D_00347FD0, 0.6f);
        Text text;
        Colour u;
        InitText(&text, 0.0f, 0.0f, 640.0f, 480.0f, 0xFF808080, u);
        {
        Font fontBig;
        func_00264880(&fontBig, D_00347FE0, 0.55f);
        float dxBig = func_00264EB0(&fontBig);
        float dyBig = fontBig.dy;
        Font fontSmall;
        func_00264880(&fontSmall, D_00347FE0, 0.35f);
        float dxSmall = func_00264EB0(&fontSmall);
        float dySmall = fontSmall.dy;
        float dxA = func_00264EB0(&fontA);
        float dyA = fontA.dy;
        float dxB = func_00264EB0(&fontB);
        float dyB = fontB.dy;
        int i;
        for (i = 0; i < p->count; i++) {
            Entry *pe = &p->entries[i];
            if (p->state == 1 || pe->done || pe->t + p->dt < t) {
                unsigned int j;
                for (j = 0; j < 4; j++) {
                    Key *pk = &D_003258C0[j];
                    float x = ((float *)&pe->pos)[0] + pk->dx * dxSmall;
                    float y = ((float *)&pe->pos)[1] + pk->dy * dySmall;
                    unsigned char ch = 'o';
                    float scale = 0.35f;
                    if (pk->id == pe->k) {
                        x -= (dxBig - dxSmall) * 0.5f;
                        y -= (dyBig - dySmall) * 0.5f;
                        ch = pk->ch;
                        scale = 0.55f;
                    }
                    u.s.a[2] = ch;
                    u.s.a[0] = '&';
                    u.s.a[1] = '2';
                    u.s.a[3] = '&';
                    u.s.a[4] = '.';
                    u.s.a[5] = 0;
                    func_00264880(&fontBig, u.s.a, scale);
                    text.x = x;
                    text.y = y;
                    func_00265480(&fontBig, &text, 0x1A);
                }
            } else {
                text.x = ((float *)&pe->pos)[0] - dxA * 0.5f;
                text.y = ((float *)&pe->pos)[1] - dyA;
                func_00265480(&fontA, &text, 0x1A);
            }
        }
        if (p->hintIndex < p->count) {
            Entry *pe = &p->entries[p->hintIndex];
            switch (p->hintState) {
            case 0:
                if (pe->t - t < 0.4f) {
                    p->vel = D_00325900;
                    p->hintState = 1;
                }
                break;
            case 1:
                if (pe->t < t) {
                    p->hintState = 0;
                    p->hintIndex = p->hintIndex + 1;
                }
                break;
            }
            if (p->hintState == 1) {
                func_00118558(GMax(pe->t - t, D_0036BB98.dt), D_0036BB98.dt, 1.0f, p->pos, p->vel, pe->pos, D_00325910, &p->pos, &p->vel, 0);
            }
        }
        text.x = ((float *)&p->pos)[0] - dxB * 0.5f;
        text.y = ((float *)&p->pos)[1] - dySmall * 3.0f - dyB - 7.0f;
        func_00265480(&fontB, &text, 0x1A);
        }
    }
}
