// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VEC { float x, y, z, w; } __attribute__((aligned(16)));
static inline qword QwFromXyzV(float gX, float gY, float gZ)
{
    qword qwXYZ;
    int iTmp;
    struct VEC vecXyz;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(qwXYZ), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
    *(qword *)&vecXyz = qwXYZ;
    return *(qword *)&vecXyz;
}
struct VTE { short delta; short pad; void (*pfn)(void *); };
struct PARAMS { float g0; float g4; float g8; float gC; float g10; float g14; };
struct ENT { int pad[3]; void *pC; int pad10; void *p14; };
struct SND { unsigned char pad[0x5A]; short h5A; };
struct Self {
    unsigned char pad0[0xC]; struct VTE *pvt;
    unsigned char pad10[0x134 - 0x10]; struct PARAMS *pparams;
    unsigned char pad138[0x1F0 - 0x138]; int state;
    unsigned char pad1F4[0x268 - 0x1F4]; float g268; int pad26C; qword v270;
    unsigned char pad280[0x284 - 0x280]; void *p284; float g288; int n28C; struct ENT a290[4]; int pad2F0[4];
    struct SND *p300; int pad304; float g308;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern unsigned char D_0036C700[];
/* .rodata curve at 0x321F50 (no symbol in symbol_addrs.txt); placed with this unit's .rodata. */
static const float D_00321F50[4] = { 1.0f, 0.0f, 0.5f, 0.0f };
void func_0023C660(struct Self *s);
int func_0019BAA0(struct Self *s);
void func_0019C570(struct Self *s, int n);
void func_001854C8(void *p, int n, struct Self *s);
void *func_001F4A80(struct Self *s);
float func_00168108(void *p, float a, float b, float c);
qword func_0011FD70(float a, float b, float c);
float func_0011E438(void *p, float g);
void func_0012F4F8(void *p, qword v);
void func_00239CE8(void *p, int n);
float func_0011E598(const void *curve, int n, float a, float b, float c);
void func_00244E08(struct SND *p, float g);
void func_00244C70(struct SND *p);
void func_00244C28(struct SND *p);
void func_0019C0B0(struct Self *s)
{
    int st;
    func_0023C660(s);
    do {
        st = s->state;
        switch (st) {
        case 2:
            if (func_0019BAA0(s)) func_0019C570(s, 1);
            break;
        case 6:
            if (func_0019BAA0(s)) {
                func_001854C8(D_0036C700, 0xC, s);
                s->pvt[9].pfn((char *)s + s->pvt[9].delta);
                return;
            }
            break;
        }
    } while (s->state != st);
    switch (s->state) {
    case 0:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 2:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 3:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 4:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 5:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 6:
        {
            int *pv = (int *)&s->v270;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
        }
        break;
    case 1: {
        int i;
        qword v;
        void *p = func_001F4A80(s);
        s->g268 = func_00168108(p, s->pparams->g0, s->pparams->g4, s->g268);
        s->v270 = func_0011FD70(s->g268, s->pparams->g8 * 1000.0f, 0.0f);
        s->g288 = func_00168108(p, s->pparams->gC, s->pparams->g10, s->g288);
        s->g288 = func_0011E438(s->p284, s->g288);
        v = QwFromXyzV(0.0f, 0.0f, s->g288);
        for (i = 0; i < s->n28C; i++) {
            struct ENT *e = &s->a290[i];
            if (e->pC) func_0012F4F8(e->pC, v);
            if (e->p14) {
                if (s->pparams->g14 > 0.0f) func_00239CE8(e->p14, 0x86);
                else func_00239CE8(e->p14, 0x84);
            }
        }
        break;
    }
    }
    if (s->p300) {
        float g = s->state == 1 ? s->pparams->g8 : 0.0f;
        s->g308 = func_0011E598(D_00321F50, 0, s->g308, g, g_clock.dt);
        func_00244E08(s->p300, s->g308);
        if (s->g308 > 0.0f) {
            if (s->p300->h5A > 0) func_00244C70(s->p300);
        } else {
            if (s->p300->h5A <= 0) func_00244C28(s->p300);
        }
    }
}
