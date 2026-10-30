// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short delta; short pad; int (*pfn)(void *); };
struct OBJ { struct VTE *pvt; };
struct ACTOR { unsigned char pad[0xC]; struct VTE *pvt; };
struct PLAYER { unsigned char pad[0x11BC]; int n11BC; int n11C0; float g11C4; };
struct ACT { unsigned char pad[0x1454]; void *p1454; };
struct SEQ { int n0; };
struct Self {
    unsigned char pad[0x10]; struct PLAYER *pplayer; unsigned char pad14[0x30 - 0x14]; struct ACT *pact; int state; float t38;
    unsigned char pad3C[0x44 - 0x3C]; struct SEQ *pseq;
    unsigned char pad48[0x54 - 0x48]; float t54; unsigned char pad58[0x6C - 0x58]; float t6C; int n70;
};
struct GAME { unsigned char pad[0x1108]; void *p1108; unsigned char pad110C[0x19E0 - 0x110C]; int n19E0;
    unsigned char pad19E4[0x1F40 - 0x19E4]; struct ACTOR *p1F40; };
struct UI { unsigned char pad[0x60]; struct OBJ *p60; struct OBJ *p64; };
extern struct CLOCK { float t; } g_clock;
extern struct GAME *D_00370AC0;
extern unsigned char D_0036C700[];
/* 0x0047A430 has no symbol of its own; reach it through the preceding D_0047A424 object. */
extern struct { unsigned char pad[0xC]; struct UI *pui; } D_0047A424;
/* .data tunable at 0x344FEC (0.33f), no symbol in symbol_addrs.txt; placed by its bytes. */
static float D_00344FEC = 0.33f;
void func_0018C1A8(struct Self *s);
void func_001ADDD0(struct GAME *g, int a, int b);
void func_0018C018(struct Self *s, int n);
void func_0018C0F8(struct Self *s, int n, void *p);
void func_00260F18(struct ACTOR *p, int a, int b, int c);
void func_00238AB8(struct Self *s);
void func_001854C8(void *p, int n, struct PLAYER *pplayer);
void func_00172AE8(void *p, int n);
#define VCALL(o, i) ((o)->pvt[i].pfn((char *)(o) + (o)->pvt[i].delta))
static inline void Stop(void)
{
    struct ACTOR *p = D_00370AC0->p1F40;
    if (p) VCALL(p, 0x36);
}
void func_0018BB20(struct Self *s, int state)
{
    int old;
    if (state == s->state) return;
    func_0018C1A8(s);
    if (s->state == 3 || s->state == 6) Stop();
    old = s->state;
    s->state = state;
    s->t38 = g_clock.t;
    switch (state) {
    case 0:
        s->pact->p1454 = s->pplayer;
        func_001ADDD0(D_00370AC0, 0x15, -1);
        break;
    case 1:
        func_001ADDD0(D_00370AC0, 0x16, -1);
        func_0018C018(s, 0);
        break;
    case 2:
        func_0018C018(s, 1);
        break;
    case 3: {
        struct OBJ *o = D_0047A424.pui->p60;
        func_0018C0F8(s, VCALL(o, 1), 0);
        s->t54 = g_clock.t + D_00344FEC;
        if (D_00370AC0->p1F40) func_00260F18(D_00370AC0->p1F40, 0x3B1, 0x3B2, 0x3B3);
        break;
    }
    case 5:
        s->t6C = g_clock.t + 0.75f;
        if (D_00370AC0->p1F40) func_00260F18(D_00370AC0->p1F40, 0x3AE, 0x3AF, 0x3B0);
        break;
    case 7:
        Stop();
        func_0018C0F8(s, s->pseq->n0, D_00370AC0);
        break;
    case 8:
        s->pplayer->n11BC = 1;
        s->pplayer->g11C4 = g_clock.t;
        s->n70 = 1;
        func_0018C018(s, 2);
        break;
    case 9: {
        struct OBJ *o;
        Stop();
        o = D_0047A424.pui->p64;
        func_0018C0F8(s, VCALL(o, 1), D_00370AC0);
        break;
    }
    case 10:
        func_0018C018(s, 3);
        break;
    case 12:
        Stop();
        func_0018C018(s, 4);
        break;
    case -1:
        func_00238AB8(s);
        Stop();
        s->pact->p1454 = 0;
        if (D_00370AC0->n19E0 == 0x16) func_001ADDD0(D_00370AC0, 0, -1);
        switch (old) {
        case 8:
            func_001854C8(D_0036C700, 0x50, s->pplayer);
            break;
        case 10:
        case 12:
            func_001854C8(D_0036C700, 0x51, s->pplayer);
            func_00172AE8(D_00370AC0->p1108, -1);
            break;
        }
        break;
    }
}
/* Next .rodata object of the original unit (button/glyph pairs at 0x321A18, read by func_0018B658); defined here so
   this unit's jump table places (the whole 16-byte padded .rodata must match). */
const int D_00321A18[8] = { 0x10, 'T', 0x20, 'O', 0x40, 'X', 0x80, 'S' };
/* ... and the one after it (button table at 0x321A38, read by func_0018C220). */
const struct { int key; unsigned char ch; float dx; float dy; } D_00321A38[4] = {
    { 0x10, 'T', 0.0f, -1.0f }, { 0x20, 'O', 1.0f, 0.0f }, { 0x40, 'X', 0.0f, 1.0f }, { 0x80, 'S', -1.0f, 0.0f },
};
