// SLY3_CFLAGS: -Os -G0 -ffast-math
// Per-frame update of the character controller: pick the next state from the input of the current one and let the
// state change function switch (repeats until the state is stable). Modelled on Sly 2 func_00134850.
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct PO { char pad0[8]; float g8; char padC[0x18 - 0xC]; int flags; char pad1C[0x2C - 0x1C]; struct VTE *vt; };
struct P {
    char pad0[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; struct PO *po;
    char pad138[0x320 - 0x138]; char a320[0x500 - 0x320]; char a500[8]; int x508;
    char pad50C[0xE40 - 0x50C]; char aE40[0xF60 - 0xE40]; char aF60[0x10DC - 0xF60];
    void *x10DC; char pad10E0[0x10F8 - 0x10E0]; int x10F8; char pad10FC[0x113C - 0x10FC];
    void *x113C; void *x1140; char pad1144[0x13E8 - 0x1144]; int x13E8; char pad13EC[0x1470 - 0x13EC];
    int state; float t1474;
};
struct CLOCK { float now, step; };
extern struct CLOCK D_0036BB98;
int func_001398F0(void *);
int func_002503C8(struct P *, float);
void func_001B7268(void *, float, int, int, int);
int func_00156998(struct P *);
int func_00153290(struct P *, int);
int func_001A7A80(struct PO *, int, float);
void func_001BDA88(void *, int, int);
void func_001B5170(void *);
void func_001B9020(void *);
void func_001B27D8(void *);
void func_001C2A18(void *);
int func_00138AC8(void *);
int func_00239CC0(void *);
void func_001F08B8(struct P *, int);

#define VCALL0(p, n) ((void (*)(void *))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d)
#define VCALL3(p, n, a) ((int (*)(void *, int))(p)->vt[n].pfn)((char *)(p) + (p)->vt[n].d, a)
#define POCHECK(po, grf, g) ((int (*)(void *, int, float))(po)->vt[1].pfn)((char *)(po) + (po)->vt[1].d, grf, g)
#define POCLEAR(po, grf) ((void (*)(void *, int))(po)->vt[2].pfn)((char *)(po) + (po)->vt[2].d, grf)
#define BLOCK() if (func_002503C8(p, 0.1f)) func_001B7268(p->a320, 1.0f, 0, 0, 0)

void func_001F0388(struct P *p)
{
    int s;
    do {
        s = p->state;
        switch (s) {
        case 8:
            if (func_001398F0(p->x10DC) || p->x10F8) {
                BLOCK();
            }
            break;
        case 6:
            if (p->x508 == 1 || p->x508 == 12)
                break;
            BLOCK();
            break;
        case 5:
        case 7:
        case 9:
        case 10:
            break;
        default:
            BLOCK();
            break;
        }
        switch (p->state) {
        case 0:
        case 1:
        case 2:
            if (func_00156998(p)) {
                func_001F08B8(p, 0);
            } else if (!(p->po->flags & 8) && !p->x13E8 && func_00153290(p, 0)) {
                func_001F08B8(p, 3);
            } else if (func_001A7A80(p->po, 0x40, 0.1f)) {
                func_001B7268(p->a320, 1.0f, 1, 0, 0);
            } else if (POCHECK(p->po, 0x400, 0.15f) && 0.1f < D_0036BB98.now - p->t1474 && VCALL3(p, 113, 3)) {
                func_001F08B8(p, 0);
                POCLEAR(p->po, 0x400);
                func_001BDA88(p->aF60, 0, 0);
            } else if (func_001A7A80(p->po, 0x20, 0.2f)) {
                func_001B5170(p->a500);
            } else {
                float g = p->po->g8;
                if ((p->state == 0 && 0.1f < g) || (p->state != 0 && 0.0f < g)) {
                    if ((p->po->flags & 8) || p->x13E8)
                        func_001F08B8(p, 1);
                    else
                        func_001F08B8(p, 2);
                } else {
                    func_001F08B8(p, 0);
                }
            }
            break;
        case 3:
        case 4:
            if (func_00156998(p)) {
                func_001F08B8(p, 3);
            } else if ((p->po->flags & 8) || p->x13E8 || !func_00153290(p, 1)) {
                func_001F08B8(p, 0);
            } else if (func_001A7A80(p->po, 0x40, 0.1f)) {
                func_001B7268(p->a320, 1.0f, 1, 0, 0);
            } else if (POCHECK(p->po, 0x400, 0.15f) && 0.1f < D_0036BB98.now - p->t1474 && VCALL3(p, 113, 3)) {
                func_001F08B8(p, 3);
                POCLEAR(p->po, 0x400);
                func_001BDA88(p->aF60, 0, 0);
            } else if (func_001A7A80(p->po, 0x20, 0.2f)) {
                func_001B5170(p->a500);
            } else if (0.0f < p->po->g8) {
                func_001F08B8(p, 4);
            } else {
                func_001F08B8(p, 3);
            }
            break;
        case 5:
            func_001B9020(p->a320);
            break;
        case 6:
            func_001B27D8(p->a500);
            break;
        case 7:
            func_001C2A18(p->aE40);
            break;
        case 8:
            if (func_001398F0(p->x10DC)) {
                if (0.0f < p->po->g8)
                    func_001F08B8(p, 2);
                else if (func_001A7A80(p->po, 0x40, 0.1f))
                    func_001B7268(p->a320, 1.0f, 1, 0, 0);
            }
            break;
        case 9:
            if (p->x113C && func_00138AC8(p->x113C))
                func_001F08B8(p, 0);
            else if (p->x1140 && func_00239CC0(p->x1140))
                func_001F08B8(p, 0);
            break;
        case 10:
            break;
        }
        VCALL0(p, 98);
    } while (p->state != s);
}
