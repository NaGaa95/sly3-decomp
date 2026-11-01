// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Re-seat the child body (p58) relative to its parent frame (p60) and a supplied point: rebuild its matrix as
// child * parent-relative * reference transform, store the new position and a fresh stamp, then refresh the dependants and
// (when the owner has a region link and the flag is set) re-register the body in its region. Based on Sly 2 func_001F40A0.
extern "C" {
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { M3 m3; qword r3; } s; float f[4][4]; qword r[4]; } __attribute__((aligned(16))) M4;
typedef union { qword q; float f[4]; } V4;
struct LO { char pad[0x30]; V4 v30; M4 m40; char pad2[0xA0 - 0x80]; struct LO *pA0; int nA4; };
struct REGION;
struct REGION_LINK;
struct E { char pad[0xDC]; struct REGION_LINK *regionLink; };
struct VTE { short d; short p; void (*pfn)(void *); };

typedef unsigned long ulong;
struct P { char pad[0xC]; struct VTE *pvt; char pad10[0x28 - 0x10]; ulong bits28; char pad30[0x48 - 0x30]; struct LO *p58; char pad4C[4]; struct LO *p60; char pad54[0xD8 - 0x54]; struct E *pe; };
struct SW { char pad[0x44F4]; int n3D58; };
extern struct SW D_00475480;
qword *func_002BA818(qword *, qword);
M4 *func_0011D768(M4 *,const M4 *);
M4 *func_0011D558(M4 *, const M4 *, const M4 *);
void *func_00292034(void *, int, int);
void func_0023DF78(struct P *);
void func_0028F260(struct P *, struct LO *);
void func_0023C8F8(struct P *);
struct REGION *func_001ED678(qword, int);
void func_0023C750(struct P *, struct REGION *);
void func_0023D0E8(struct P *p, qword v)
{
    M4 m0, m40, m80, mC0, m100, m140, m180, m1C0;
    struct LO *plo;
    const M3 *basis;
    M4 *presult;
    if (!p->p58) return;
    basis = &p->p60->m40.s.m3;
    func_002BA818(&m0.s.r3, v);
    m0.s.m3 = *basis;
    m0.f[1][3] = 0.0f;
    m0.f[2][3] = 0.0f;
    m0.f[0][3] = 0.0f;
    m0.f[3][3] = 1.0f;
    presult=&mC0;
    func_0011D768(&m100,&p->p58->m40);
    func_0011D558(presult, &m100, &p->p60->m40);
    m40.r[0] = mC0.r[0];
    m40.r[1] = mC0.r[1];
    m40.r[2] = mC0.r[2];
    m40.r[3] = mC0.r[3];
    if (p->p58->pA0) {
        m80 = p->p58->pA0->m40;
    } else {
        M4 *identity = &m80;
        func_00292034(identity, 0, 0x40);
        identity->f[3][3] = 1.0f;
        identity->f[2][2] = 1.0f;
        identity->f[1][1] = 1.0f;
        m80.f[0][0] = 1.0f;
    }
    M4 *world=&m140;
    func_0011D768(&m180,&m80);
    func_0011D558(world, &m180, &m0);
    func_0011D768(&m1C0,&m40);
    func_0011D558(&m100, world, &m1C0);
    plo = p->p58;
    mC0 = m100;
    func_002BA818(&plo->v30.q, mC0.r[3]);
    plo->v30.f[3] = 1.0f;
    { int stamp=++D_00475480.n3D58;p->p58->nA4=stamp; }
    p->pvt[20].pfn((char *)p + p->pvt[20].d);
    func_0023DF78(p);
    func_0028F260(p, p->p58);
    func_0023C8F8(p);
    {
        struct REGION_LINK *link = 0;
        if (p->pe) link = p->pe->regionLink;
        if (link && ((int)(p->bits28 >> 56) & 1)) {
            VTE *entry = &p->pvt[36];
            func_0023C750(p, func_001ED678(((M4 *(*)(void *))entry->pfn)((char *)p + entry->d)->r[3], 1));
        }
    }
}

}
