// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Per-frame update of a carried/attached object: mask the holder's 128-bit flag set, aim toward the target. */
typedef int qword __attribute__((mode(TI)));
struct GRF {
    unsigned char ab[16];
    GRF operator&(const GRF &o) const { GRF r; for (int i = 0; i < 16; i++) r.ab[i] = ab[i] & o.ab[i]; return r; }
    GRF operator~() const { GRF r; for (int i = 0; i < 16; i++) r.ab[i] = ~ab[i]; return r; }
    GRF &operator&=(const GRF &o) { for (int i = 0; i < 16; i++) ab[i] &= o.ab[i]; return *this; }
    GRF &operator|=(const GRF &o) { for (int i = 0; i < 16; i++) ab[i] |= o.ab[i]; return *this; }
};
struct M3 { qword r[3]; };
struct V4 { float a[4]; };
struct VTE { short delta; short pad; void *(*method)(void *); };
struct POS { float f0, f4; };
struct POSQ { char pad[0x30]; qword pos; };
struct OBJ { char pad[0xC]; VTE *vt; };
struct HOLDER { char pad[0xC]; VTE *vt; char pad10[0x2F4 - 0x10]; GRF grf; char pad304[0x10F0 - 0x304]; int x10F0; };
struct SELF { char pad[0x10]; HOLDER *p10; char pad14[0x50 - 0x14]; M3 m50; int x80; char pad84[0x90 - 0x84]; qword q90;
    char padA0[0xB0 - 0xA0]; qword qB0; OBJ *pC0; int xC4; int xC8; int xCC; };
extern "C" {
extern GRF D_0036B240;
extern GRF D_00475440;
extern qword D_00317550;
qword func_0023ED38(HOLDER *);
int func_0013B500(OBJ *, int);
void func_0022EA88(OBJ *, qword, int, qword *, qword *, int, float *);
float func_001205C8(qword);
float func_002A3EE8(float, float);
GRF func_00252AD0(int);
float func_0011E3B8(float);
void func_0011C8C0(M3 *, qword, float);
void func_001F32E8(OBJ *, int, M3 *, float);
void func_001327A8(SELF *);
void func_00198D78(qword *, int, int, float, float);
void func_00131598(SELF *);
void func_00132930(SELF *, qword);
void func_00133510(SELF *, int);
void func_00132C58(SELF *, int);
void func_00132438(SELF *);
void func_0024E8E8(HOLDER *, qword);
void func_002389C0(SELF *);
}
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }


extern "C" void func_00131E10(SELF *p)
{
    p->q90 = func_0023ED38(p->p10);
    GRF grfSave = p->p10->grf & D_0036B240;
    p->p10->grf &= ~D_0036B240;
    GRF grfAdd = D_00475440;
    if (p->pC0) {
        float g;
        M3 m;
        float sHit;
        if (func_0013B500(p->pC0, 9)) {
            OBJ *pc = p->pC0;
            V4 vDir;
            func_0022EA88(pc, ((POSQ *)VCALL(p->p10, 36))->pos, 0, &p->qB0, (qword *)&vDir, 0, &sHit);
            g = func_001205C8(*(qword *)&vDir);
        } else {
            p->qB0 = ((POSQ *)VCALL(p->pC0, 36))->pos;
            POS *pp = (POS *)VCALL(p->pC0, 36);
            g = func_002A3EE8(pp->f4, pp->f0);
        }
        if (func_0013B500(p->pC0, 0xC)) {
            grfAdd |= func_00252AD0(0x2F);
            if (!p->xC4)
                g = func_0011E3B8(g + 3.14159265f);
            p->x80 = 1;
            func_0011C8C0(&m, D_00317550, g);
            p->m50 = m;
        } else if (func_0013B500(p->pC0, 0x25)) {
            grfAdd |= func_00252AD0(0x3A);
        } else if (func_0013B500(p->pC0, 0xA)) {
            grfAdd |= func_00252AD0(0x39);
            p->x80 = 1;
            func_001F32E8(p->pC0, p->xC4, &p->m50, sHit);
            func_001327A8(p);
        } else {
            if (p->xC8)
                func_00198D78(&p->qB0, 0, 0, 100.0f, -350.0f);
            p->pC0 = 0;
        }
    }
    p->p10->grf |= grfAdd;
    func_00131598(p);
    p->p10->grf &= ~grfAdd;
    p->p10->grf |= grfSave;
    func_00132930(p, p->qB0);
    switch (p->xCC) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        func_00133510(p, 0);
        func_00132C58(p, 1);
        func_00132438(p);
        break;
    case 0:
        func_00132C58(p, 0);
        break;
    default: {
        HOLDER *ph = p->p10;
        int k = ph->x10F0;
        if (k >= -1 && (k <= 0 || k == 2)) {
            qword v = p->qB0;
            func_0024E8E8(p->p10, Sub(v, ((POSQ *)VCALL(ph, 36))->pos));
        }
        func_00132C58(p, 0);
        break;
    }
    }
    func_002389C0(p);
}
