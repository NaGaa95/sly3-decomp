// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *pfn; };
struct HIT { unsigned char pad[0x30]; qword q30; };
struct LINK { unsigned char pad[0x30]; int n30; };
struct Self {
    unsigned char pad0[0xC]; struct VTE *pvt;
    unsigned char pad10[0x1A0 - 0x10]; qword v1A0;
    unsigned char pad1B0[0x320 - 0x1B0]; unsigned char ab320[0x508 - 0x320];
    int n508; int pad50C[2]; int n514;
    unsigned char pad518[0x113C - 0x518]; int n113C; struct LINK *p1140; int n1144;
    unsigned char pad1148[0x11B4 - 0x1148]; char *p11B4;
    unsigned char pad11B8[0x19E0 - 0x11B8]; int n19E0;
    unsigned char pad19E4[0x19F4 - 0x19E4]; int n19F4;
    unsigned char pad19F8[0x1C2C - 0x19F8]; int n1C2C;
    unsigned char pad1C30[0x1D4C - 0x1C30]; int n1D4C;
};
void func_00153738(struct Self *p, int msg, void *arg);
void func_001ADDD0(struct Self *p, int a, int b);
int func_0013B500(void *p, int k);
void *func_002387A8(void *p, int k);
void func_0016E118(void *p, int n);
void func_00156DC0(struct Self *p, qword q, int n);
void func_001B7268(void *p, int a, int b, int c, float g);
#define VCALL(o, i, T) ((T)(o)->pvt[i].pfn)((char *)(o) + (o)->pvt[i].delta
void func_001AA988(struct Self *p, int msg, void *arg)
{
    func_00153738(p, msg, arg);
    switch (msg) {
    case 5:
        if ((int)arg == p->n113C) {
            switch (p->n19E0) {
            case 0xB:
                func_001ADDD0(p, 0, -1);
                break;
            case 8:
                p->n1144 = -1;
                break;
            }
        }
        break;
    case 10: {
        int *pn = (int *)arg;
        if (pn[0] != p->n113C) {
            if (!p->p1140) break;
            if (pn[0] != p->p1140->n30) break;
        }
        switch (pn[2]) {
        case 0x185:
            if (p->p11B4 && func_0013B500(p->p11B4, 0x3A) && p->n1C2C) {
                struct HIT *phit = VCALL(p, 0x24, struct HIT *(*)(void *)));
                func_00156DC0(p, phit->q30, 1);
            }
            break;
        case 0x2A6:
            p->n1D4C = 1;
            {
                int *pv = (int *)&p->v1A0;
                pv[2] = 0;
                pv[1] = 0;
                pv[0] = 0;
            }
            VCALL(p, 0x28, void (*)(void *, qword)), p->v1A0);
            if (func_0013B500(p->p11B4, 0x3A)) {
                void *pv = func_002387A8(p->p11B4 + 0x29C, 0xDA);
                if (pv) func_0016E118(pv, 4);
            }
            break;
        case 0x2A7:
            if (func_0013B500(p->p11B4, 0x3A)) {
                void *pv = func_002387A8(p->p11B4 + 0x29C, 0xDA);
                if (pv) func_0016E118(pv, 6);
            }
            break;
        }
        break;
    }
    case 1:
        switch (p->n19E0) {
        case 4:
        case 0x11:
            if (p->n19F4 == (int)arg) func_001B7268(p->ab320, 0, 0, 0, 1.0f);
            break;
        case 8:
            switch (p->n508) {
            case 3:
            case 4:
                if (p->n514 == (int)arg) func_001B7268(p->ab320, 0, 0, 0, 1.0f);
                break;
            }
            break;
        }
        break;
    }
}
