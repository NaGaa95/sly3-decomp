// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* State update of the 0x143230 / 0x1434A8 family; owns jump table 0x3200A0. */
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct LM { float gMin, gMax; };
struct VTE { short d; short pad; struct M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; struct VTE e120; };
struct H { float g0; float g4; float g8; };
struct P {
    char pad[0xC]; struct VT *pvt; char pad1[0x134 - 0x10]; struct H *p134; char pad2[0x1E0 - 0x138]; float g1E0; float g1E4;
    char pad3[0x2B8 - 0x1E8]; int x2B8; float g2BC; int x2C0; int x2C4; float g2C8; float g2CC; float g2D0; float g2D4;
    int x2D8; float g2DC; char pad4[0x4BC - 0x2E0]; int x4BC;
};
extern struct CLOCK { float t; } g_clock;
extern float D_0047A2B0;
extern struct LM D_003201F8;
void func_00142AE0(struct P *p, int n);
void func_00143230(struct P *p, int st);
void func_001434A8(struct P *p, int st);
int func_001A7A80(struct H *p, int button, float t);
float func_0011E940(float gMin, float gMax);
void func_00143AB8(struct P *p);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }

void func_00143628(struct P *p)
{
    int st, sub;
    do {
        st = p->x2B8;
        sub = p->x2C0;
        switch (st) {
        case 0: {
            int f = D_0047A2B0 < GetZ(p->pvt->e120.pfn((char *)p + p->pvt->e120.d)->r[3]);
            if (f) {
                func_00142AE0(p, 3);
                break;
            }
            if (p->x4BC)
                break;
            if (func_001A7A80(p->p134, 0x10, 0.25f)) {
                func_00143230(p, 5);
                break;
            }
            if (func_001A7A80(p->p134, 0x20, 0.25f))
                p->g2CC = g_clock.t;
            if (p->g2CC <= g_clock.t) {
                if (g_clock.t - p->g2CC < 0.2f) {
                    if (0.1f < p->p134->g8 && __builtin_fabsf(p->p134->g4) > __builtin_fabsf(p->p134->g0)) {
                        if (0.0f < p->p134->g4)
                            func_00143230(p, 4);
                        else
                            func_00143230(p, 3);
                    } else if (D_003201F8.gMin < p->p134->g8) {
                        if (0.0f < p->p134->g0)
                            func_00143230(p, 2);
                        else
                            func_00143230(p, 1);
                    }
                } else if (func_0011E940(0.0f, 1.0f) < 0.5f) {
                    func_00143230(p, 1);
                } else {
                    func_00143230(p, 2);
                }
            }
            break;
        }
        case 1:
        case 2:
            if (sub == 3)
                func_00143230(p, 0);
            break;
        case 3:
            if (sub != 3)
                break;
            switch (p->x2C4) {
            case 0:
                p->g2D0 = -3.14159274f - p->g1E4;
                func_001434A8(p, 2);
                break;
            case 2:
                p->g2D0 = p->g1E0 < 0.0f ? -3.14159274f : 3.14159274f;
                func_001434A8(p, 1);
                p->g2D4 *= 1.5f;
                break;
            default:
                func_00143230(p, 0);
                break;
            }
            break;
        case 4:
            if (sub == 3) {
                switch (p->x2C4) {
                case 0:
                    if (p->g2D0 < 0.0f)
                        p->g2D0 = -3.14159274f;
                    else
                        p->g2D0 = 3.14159274f;
                    func_001434A8(p, 1);
                    p->g2D4 *= 1.5f;
                    break;
                case 1:
                    p->g2D0 = p->g1E4 + -3.14159274f;
                    func_001434A8(p, 2);
                    break;
                default:
                    func_00143230(p, 0);
                    break;
                }
            } else if (sub == 2) {
                if (g_clock.t - p->g2C8 > p->g2D4 * 0.6f && !p->x2D8) {
                    p->x2D8 = 1;
                    p->g2DC = g_clock.t;
                }
            }
            break;
        case 5:
            if (sub == 3) {
                if (p->x2C4 == 0) {
                    p->g2D0 = -6.28318548f - p->g1E4;
                    func_001434A8(p, 2);
                    p->g2D4 += p->g2D4;
                } else {
                    func_00143230(p, 0);
                }
            } else if (sub == 2) {
                if (g_clock.t - p->g2C8 > p->g2D4 * 0.8f && !p->x2D8) {
                    p->x2D8 = 1;
                    p->g2DC = g_clock.t;
                }
            }
            break;
        }
        func_00143AB8(p);
    } while (st != p->x2B8 || sub != p->x2C0);
}
