// SLY3_CFLAGS: -Os -fno-regmove -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3: fire slot-93 vcall from one of four source modes (curve point, curve+target, object, aim); -fno-regmove keeps r/v in separate stack slots.
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct LO {
    char pad[12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual XF *PxfGet();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void w43();
    virtual void w44();
    virtual void w45();
    virtual void w46();
    virtual void w47();
    virtual void w48();
    virtual void w49();
    virtual void w50();
    virtual void w51();
    virtual void w52();
    virtual void w53();
    virtual void w54();
    virtual void w55();
    virtual void w56();
    virtual void w57();
    virtual void w58();
    virtual void w59();
    virtual void w60();
    virtual void w61();
    virtual void w62();
    virtual void w63();
    virtual void w64();
    virtual void w65();
    virtual void w66();
    virtual void w67();
    virtual void w68();
    virtual void w69();
    virtual void w70();
    virtual void w71();
    virtual void w72();
    virtual void w73();
    virtual void w74();
    virtual void w75();
    virtual void w76();
    virtual void w77();
    virtual void w78();
    virtual void w79();
    virtual void w80();
    virtual void w81();
    virtual void w82();
    virtual void w83();
    virtual void w84();
    virtual void w85();
    virtual void w86();
    virtual void w87();
    virtual void w88();
    virtual void w89();
    virtual void w90();
    virtual void w91();
    virtual void Fire(int, void *, qword, qword, qword);
};
struct PAIR { void *p0; void *p4; };
struct P : LO {
    char pad1[0x10F0 - 0x10]; int n10F0; LO *p10F4; float f10F8; int pad10FC; LO *p1100;
    char pad2[0x1730 - 0x1104]; PAIR *p1730; char pad3[0x1740 - 0x1734]; qword q1740; qword q1750;
};
struct VEC { float f[4]; } __attribute__((aligned(16)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
extern "C" {
extern qword D_00317530, D_00317540, D_00317550;
void func_0023E108(P *);
void func_0022E330(void *pmesh, float g, qword *ppos, qword *pnormal);
qword func_00250600(P *);
qword func_0028E910(void *, int, qword);
void func_0011FEA8(qword a, qword b, qword c, qword *pm);
void func_00255570(P *p);
}
static const float RO_00327480[4] __attribute__((aligned(16))) = { 37.0f, 0.0f, 25.0f, 0.0f };
static inline qword MulS(VU_FLOAT b, qword a) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(b.q)); return r; }
static inline qword Load(const float *p) { qword r; __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*(const qword *)p)); return r; }
static inline qword Xform(qword v, qword a, qword b, qword c)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(a), "j"(b), "j"(c));
    return r;
}
static inline qword Sub(qword a, qword b) { __asm__("vsub.xyzw %0, %0, %1" : "=j"(a) : "j"(b), "0"(a)); return a; }

void func_00255570(P *p)
{
    func_0023E108(p);
    switch (p->n10F0) {
    case 0: {
        VEC pos, normal;
        func_0022E330(p->p10F4, p->f10F8, (qword *)&pos, (qword *)&normal);
        p->Fire(7, p->p10F4, *(qword *)&pos, *(qword *)&normal, func_00250600(p));
        break;
    }
    case 1: {
        VEC pos, normal;
        func_0022E330(p->p10F4, p->f10F8, (qword *)&pos, (qword *)&normal);
        p->Fire(7, p->p10F4, *(qword *)&pos, *(qword *)&normal, p->p1100->PxfGet()->pos);
        break;
    }
    case 2:
        p->Fire(7, p->p10F4, p->p10F4->PxfGet()->pos, D_00317530, func_00250600(p));
        break;
    case 3: {
        qword r = func_0028E910(p->p1730->p0, 0, p->q1740);
        qword nq = MulS(VU_FLOAT(-1.0f), p->q1750);
        VEC m[3];
        *(qword *)&m[0] = nq;
        func_0011FEA8(nq, D_00317550, D_00317540, (qword *)&m[1]);
        qword v = Sub(r, Xform(Load(RO_00327480), *(qword *)&m[0], *(qword *)&m[1], *(qword *)&m[2]));
        p->Fire(7, p->p1730->p4, v, D_00317540, p->PxfGet()->pos);
        break;
    }
    }
}
