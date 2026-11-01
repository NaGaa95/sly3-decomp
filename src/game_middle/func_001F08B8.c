// SLY3_CFLAGS: -Os -G0 -ffast-math
// SLY3_AS: gnu-2.9
// State change of a character controller: shut down what the old state had running, then set up the new state
// (animation, speed scale, velocity reset) and restart the shared playback. Modelled on Sly 2 func_00135248.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct VO { char pad[0xC]; struct VTE *vt; };
struct ASEG { char pad[0x64]; float g64; };
struct ASEGP { int x0; struct ASEG *pasega; };
struct X113C { char pad[0x14]; struct ASEG *pasega; char pad1[0x1C - 0x18]; float g1C; };
struct P {
    char pad0[0xC]; struct VTE *vt; char pad10[0x48 - 0x10]; void *p48; void *p4C;
    char pad50[0x1A0 - 0x50]; float vel[3]; char pad1AC[4]; float g1B0;
    char pad1B4[0x320 - 0x1B4]; char a320[0x500 - 0x320]; char a500[8]; int x508;
    char pad50C[0xE40 - 0x50C]; char aE40[0xF60 - 0xE40]; char aF60[0x1134 - 0xF60];
    void *p1134; char pad1138[4]; struct X113C *p113C; int x1140; int x1144;
    char pad1148[0x1164 - 0x1148]; int x1164; char pad1168[0x1470 - 0x1168];
    int state; float t1474; char pad1478[0x1480 - 0x1478]; struct ASEGP x1480;
    char pad1488[0x1530 - 0x1488]; struct ASEGP x1530; char pad1538[0x15E0 - 0x1538];
    void *p15E0; char pad15E4[0x16F0 - 0x15E4]; struct ASEG *p16F0; struct VO *p16F4; struct VO *p16F8;
};
struct CLOCK { float now, step; };
extern struct CLOCK D_0036BB98;
extern qword D_00317560;
void func_0028F068(struct P *, void *, int);
void func_00155328(struct P *);
void func_001B77F8(void *, int, int);
void func_001B4430(void *, int);
void func_001C21F0(void *, int);
void func_001FE728(struct VO *, int);
void func_00258F28(struct ASEGP *);
void func_001BDBB0(void *, int);
void func_00137628(struct X113C **);
void func_0023AC58(int *);
void func_00137588(struct ASEG *, struct P *, int, struct X113C **, float, float);
void func_0023AB98(void *, struct P *, int, int, int, int *);
int func_00239A78(void *, int);
void func_00155310(struct P *, int);

static inline void ZeroVec(float *pv) { pv[2] = 0; pv[1] = 0; pv[0] = 0; }
#define ZEROVEL() ZeroVec(p->vel)
#define VCALL0(p, n) ((void (*)(void *))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d)
#define VCALLI(p, n) ((int (*)(void *))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d)

void func_001F08B8(struct P *p, int k)
{
    int kOld;
    struct ASEG *pasega;
    void *pjt;
    int c;
    int anim;
    int n;
    float g;
    struct ASEGP *pa;

    if (k == p->state)
        return;
    switch (p->state) {
    case 0:
        func_0028F068(p, p->p48, 2);
        func_0028F068(p, p->p4C, 2);
        func_00155328(p);
        break;
    case 5:
        if (p->x1164 == 0) {
            struct VO *po = 0;
            switch (k) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 8:
                po = p->p16F4;
                break;
            case 6:
                switch (p->x508) {
                case 1:
                    break;
                case 3:
                case 4:
                    po = p->p16F8;
                    break;
                default:
                    po = p->p16F4;
                    break;
                }
                break;
            }            if (po)
                func_001FE728(po, 1);
        }
        func_001B77F8(p->a320, -1, 0);
        break;
    case 6:
        func_001B4430(p->a500, -1);
        break;
    case 7:
        func_001C21F0(p->aE40, -1);
        break;
    case 1:
    case 2:
        p->g1B0 = p->p113C->g1C / p->p113C->pasega->g64;
        break;
    case 3:
        func_0028F068(p, p->p48, 2);
        func_0028F068(p, p->p4C, 2);
        break;
    case 9:
        func_0028F068(p, p->p48, 2);
        func_0028F068(p, p->p4C, 2);
        break;
    }
    kOld = p->state;
    p->state = k;
    pasega = 0;
    pjt = 0;
    n = 1;
    anim = -1;
    c = 4;
    g = 0.0f;
    p->t1474 = D_0036BB98.now;
    switch (k) {
    case -1:
        break;
    case 0:
        func_0028F068(p, p->p48, 1);
        func_0028F068(p, p->p4C, 1);
        pjt = p->p1134;
        switch (kOld) {
        case 2:
            anim = 0x193;
            break;
        case 5:
            anim = 0x195;
            break;
        case 8:
            anim = 0x197;
            break;
        default:
            anim = 0x192;
            break;
        }
        if (func_00239A78(pjt, anim) < 0)
            anim = -1;
        *(qword *)p->vel = D_00317560;
        c = VCALLI(p, 111);
        func_00155310(p, 1);
        break;
    case 1:
        pasega = p->x1480.pasega;
        pa = &p->x1480;
        g = p->g1B0 * pasega->g64;
        func_00258F28(pa);
        n = 9;
        break;
    case 2:
        pasega = p->x1530.pasega;
        pa = &p->x1530;
        g = p->g1B0 * pasega->g64;
        func_00258F28(pa);
        n = 9;
        break;    case 3:
        func_0028F068(p, p->p48, 1);
        func_0028F068(p, p->p4C, 1);
        pjt = p->p15E0;
        ZEROVEL();
        break;
    case 4:
        pasega = p->p16F0;
        p->x1144 = -1;
        n = 9;
        ZEROVEL();
        break;
    case 7:
        func_001BDBB0(p->aF60, -1);
        break;
    case 9:
        func_0028F068(p, p->p48, 1);
        func_0028F068(p, p->p4C, 1);
        ZEROVEL();
        break;
    case 8:
        ZEROVEL();
        break;
    }
    func_00137628(&p->p113C);
    func_0023AC58(&p->x1140);
    func_00137588(pasega, p, n, &p->p113C, g, 1.0f);
    func_0023AB98(pjt, p, anim, n, c, &p->x1140);
    VCALL0(p, 101);
}
