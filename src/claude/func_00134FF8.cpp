// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Transform the position of the attached object (or of this ALO) by the ALO matrix; slot-36 virtual returns the XF.
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
struct M4 { qword r[4]; };
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
};
struct ALO : LO {
    char pad2[0x176C - 0x10];
    LO *pobj;
    char pad3[0x1780 - 0x1770];
    M4 mat;
};
struct S { char pad[0x10]; ALO *palo; };
static inline qword MulPos(const M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
            : "=j"(r) : "j"(v), "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
static inline qword PosGet(LO *p)
{
    return p->PxfGet()->pos;
}
extern "C" qword func_00134FF8(S *ps);
qword func_00134FF8(S *ps)
{
    ALO *palo = ps->palo;
    LO *po = palo->pobj;
    qword pos;
    if (po)
        pos = po->PxfGet()->pos;
    else
        pos = palo->PxfGet()->pos;
    return MulPos(&ps->palo->mat, pos);
}
