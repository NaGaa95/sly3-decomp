// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001B61A0: gather the grab candidates around the hero from every object list and hand them to the queue.
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta, pad; void *fn; };
struct M4 { qword r[4]; };
struct ACTOR { char pad0[0xC]; VTE *vt; };
struct ENTRY {
    int key; void *source; float time; int kind; char pad10[0x20];
} __attribute__((aligned(16)));
struct INFO44 { char pad[0x44]; };
struct INFO54 { char pad[0x54]; };
struct INFO28 { char pad[0x28]; };
struct INFO40 { char pad[0x40]; };
struct PAD_D0 { char pad[0xD0]; };
struct PAD_180 { char pad[0x180]; };
struct PAD_120 { char pad[0x120]; };
struct PAD_EC { char pad[0xEC]; };
struct PAD_2F0 { char pad[0x2F0]; };
struct PAD_130 { char pad[0x130]; };
struct LIST180 : PAD_180, INFO44 { LIST180 *next; };
struct LIST_D0 : PAD_D0, INFO44 {
    LIST_D0 *next; char pad118[0x1A0 - 0x118]; int x1A0; char pad1A4[0x1B0 - 0x1A4]; int x1B0;
};
struct LIST2F0 : PAD_2F0, INFO28 { LIST2F0 *next; };
struct LIST120 : PAD_120, INFO44 { LIST120 *next; };
struct LIST_EC : PAD_EC, INFO54 { LIST_EC *next; };
struct LIST130 : PAD_130, INFO40 { LIST130 *next; };
struct LINK { char pad0[0x14]; int id2; int id; };
struct GAME {
    char pad0[0x18]; int x18; char pad1C[0x4E78 - 0x1C]; int x4E78; char pad4E7C[0x4E84 - 0x4E7C]; LINK *x4E84;
    char pad4E88[0x4E90 - 0x4E88]; void *x4E90; float x4E94; char pad4E98[0x4EA0 - 0x4E98]; qword x4EA0;
    char pad4EB0[0x4F40 - 0x4EB0]; int x4F40;
};

extern "C" {
extern LIST180 *D_00479B14, *D_00479AF0, *D_00479AE4;
extern LIST_D0 *D_00479B20, *D_00479B2C, *D_00479B38, *D_00479AFC;
extern LIST2F0 *D_00479BB0;
extern LIST120 *D_00479B50;
extern LIST_EC *D_00479B44;
extern LIST130 *D_00479BA4;
extern char D_00475480[];
extern char D_0046F770[];
extern int D_0047A3C0;
extern float D_00345700, D_00345704;
int func_001F4350(ACTOR *, int);
void *func_00292034(void *, int, int);
int func_0013B500(void *, int);
int func_001A29B0(void *);
int func_002496C8(void *);
void func_001B5E18(void *, ACTOR *, qword, void *, void *, int, ENTRY *);
void func_001B6B10(GAME *, ACTOR *, int, ENTRY *);
void func_001B67C0(GAME *, ACTOR *, int, ENTRY *);
int func_0021E968(void *);
LINK *func_001FC118(void *);
void func_0021E930(void *, int);
void func_0021E870(void *, int, float);
}

static inline int Flags(ACTOR *p) { VTE &v = p->vt[106]; return ((int (*)(void *))v.fn)((char *)p + v.delta); }
static inline M4 *Matrix(ACTOR *p) { VTE &v = p->vt[36]; return ((M4 *(*)(void *))v.fn)((char *)p + v.delta); }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GetX(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline float Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return GetX(l);
}

extern "C" void func_001B61A0(void *game, ACTOR *owner)
{
    if (!func_001F4350(owner, -1))
        return;
    int flags = Flags(owner);
    ENTRY entries[4];
    func_00292034(entries, 0, sizeof(entries));
    for (unsigned i = 0; i < 4; i++) {
        entries[i].kind = -1;
        entries[i].time = D_00345704;
    }
    qword pos = Matrix(owner)->r[3];

    if (flags & 8) {
        for (LIST180 *o = D_00479B14; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 0x10) {
        for (LIST_D0 *o = D_00479B20; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 0x180) {
        for (LIST_D0 *o = D_00479B38; o; o = o->next) {
            if (func_0013B500(o, 0x22) && !(flags & 0x100))
                continue;
            if (func_0013B500(o, 0x23) && (o->x1A0 || o->x1B0))
                continue;
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
        }
    }
    if (flags & 0x2000) {
        for (LIST2F0 *o = D_00479BB0; o; o = o->next) {
            if (owner == (ACTOR *)o)
                continue;
            if (*(int *)((char *)o + 0x127C))
                func_001B5E18(game, owner, pos, o, (INFO28 *)o, 4, entries);
        }
    }
    if (flags & 4) {
        for (LIST120 *o = D_00479B50; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 0x400) {
        for (LIST_D0 *o = D_00479AFC; o; o = o->next) {
            if (func_002496C8(o))
                continue;
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
        }
    }
    if (flags & 0x200) {
        for (LIST180 *o = D_00479AF0; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 2) {
        for (LIST180 *o = D_00479AE4; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 1) {
        for (LIST_EC *o = D_00479B44; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO54 *)o, 4, entries);
    }
    if (flags & 0x20) {
        for (LIST_D0 *o = D_00479B2C; o; o = o->next)
            func_001B5E18(game, owner, pos, o, (INFO44 *)o, 4, entries);
    }
    if (flags & 0x1000) {
        for (LIST130 *o = D_00479BA4; o; o = o->next) {
            if (func_001A29B0(o))
                continue;
            func_001B5E18(game, owner, pos, o, (INFO40 *)o, 4, entries);
        }
    }

    int n = 4;
    while (n > 0 && !entries[n - 1].key)
        n--;
    GAME *g = (GAME *)D_00475480;
    func_001B6B10(g, owner, n, entries);
    func_001B67C0(g, owner, n, entries);
    int current = func_0021E968(D_0046F770);
    if (current != -1 && current != g->x4F40)
        return;
    int hint;
    if (!g->x4E78) {
        hint = -1;
    } else {
        int far = D_00345700 < Length(Sub(pos, g->x4EA0));
        if (far) {
            hint = -1;
        } else {
            LINK *link = g->x4E90 ? func_001FC118(g->x4E90) : 0;
            if (link && link->id == 0x6F8 && 1.0f < g->x4E94)
                hint = 0x1E6;
            else
                hint = ((GAME *)D_00475480)->x4E84->id2;
        }
    }
    if (hint != current) {
        if (hint == -1)
            func_0021E930(D_0046F770, D_0047A3C0);
        else
            func_0021E870(D_0046F770, hint, -1.0f);
        D_0047A3C0 = hint;
    }
}
