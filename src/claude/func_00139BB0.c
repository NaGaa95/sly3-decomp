// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
/* Gather situation flags (facing, target side, target state, own state). */
typedef int qword __attribute__((mode(TI)));
struct VTE { short delta; short pad; void *(*method)(void *); };
struct POS { float f0, f4; };
struct POSQ { char pad[0x30]; qword pos; };
struct S134 { char pad[8]; float g8; };
struct TGT { char pad[0xC]; struct VTE *vt; char pad10[0x10D0 - 0x10]; void *p10D0; };
struct P { char pad[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; struct S134 *p134; char pad138[0x1BC - 0x138]; float g1BC;
    char pad1C0[0x508 - 0x1C0]; int x508; char pad50C[0x110C - 0x50C]; float g110C; char pad1110[0x11B4 - 0x1110];
    struct TGT *ptgt; char pad11B8[0x11BC - 0x11B8]; int x11BC; };
float func_002A3EE8(float, float);
float func_0011E3B8(float);
qword func_001C94E8(void *, void *, qword);
int func_0013B500(struct TGT *, int);
int func_002533C0(struct TGT *, int);
int func_00170500(void *, struct P *);
int func_002503C8(struct P *, float);
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GAbs(float g) { return __builtin_fabsf(g); }

int func_00139BB0(struct P *p)
{
    int grf;
    int st;
    if (p->p134->g8 == 0.0f)
        grf = 0x1000;
    else {
        struct POS *pp = (struct POS *)VCALL(p, 36);
        float d = func_0011E3B8(p->g110C - func_002A3EE8(pp->f4, pp->f0));
        float ad = GAbs(d);
        if (ad < 0.7853981634f)
            grf = 0x100;
        else if (2.3561944902f < ad)
            grf = 0x800;
        else if (!(0.0f < d))
            grf = 0x200;
        else
            grf = 0x400;
    }
    if (p->ptgt) {
        qword a = ((struct POSQ *)VCALL(p->ptgt, 36))->pos;
        qword r = func_001C94E8(0, p, Sub(a, ((struct POSQ *)VCALL(p, 36))->pos));
        if (0.0f < Y(r))
            grf |= 4;
        else
            grf |= 8;
    } else {
        struct POS *pp = (struct POS *)VCALL(p, 36);
        if (func_0011E3B8(func_002A3EE8(pp->f4, pp->f0) - p->g1BC) < 0.0f)
            grf |= 4;
        else
            grf |= 8;
    }
    if (!p->ptgt || !func_0013B500(p->ptgt, 0x3A))
        grf |= 0x10;
    else if (p->x11BC == 3)
        grf |= 0x80;
    else {
        struct TGT *ptgt = p->ptgt;
        if (func_002533C0(ptgt, 6) || func_002533C0(ptgt, 0x2A))
            grf |= 0x80;
        else {
            int n = func_00170500(ptgt->p10D0, p);
            if (n > 0)
                grf |= 0x40;
            else if (!(n < -1))
                grf |= 0x20;
            else
                grf |= 0x40;
        }
    }
    st = (int)VCALL(p, 100);
    switch (st) {
    case 0:
    case 9:
        if (func_002503C8(p, 0.1f))
            grf |= 0x10000;
        else
            grf |= 0x20000;
        break;
    case 1:
        grf |= 0x10000;
        break;
    case 2:
        if (p->x508 < 5) {
            if (p->x508 >= 3)
                break;
        }
    default:
        grf |= 0x20000;
        break;
    }
    grf |= (st == 10) ? 0x100000 : 0x200000;
    return grf;
}
