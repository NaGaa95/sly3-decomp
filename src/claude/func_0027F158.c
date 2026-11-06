// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from Sly 2 func_00227BB8 (Sly 3 also tests the centre against the world).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct S { char pad[0xD0]; char aD0[0xC]; void *xDC; int c; qword *points; char pad1[0x18]; qword v100; float g110; int x114; };
extern float D_00329530;
extern qword D_00317570;
void func_0028FDE0(struct S *p, void *pbis);
void func_001193F8(void *pbis, void *pv);
void func_00119640(void *pbis, void *pv, void *pv2);
qword func_00120E80(int c, qword *points);
qword func_00120EB0(int c, qword *points);
int func_00119C90(void *p, int mask, qword v);
void func_0027F158(struct S *p, void *pbis)
{
    func_0028FDE0(p, pbis);
    func_001193F8(pbis, &p->c);
    func_00119640(pbis, &p->c, p->aD0);
    if (p->c > 0) {
        VU u;
        qword a, b, m, one, h, s; register int g asm("$3"); // pin: v1 for the radius bits
        a = func_00120E80(p->c, p->points);
        __asm__("qmtc2.ni %1,%0" : "=j"(a) : "r"(a));
        b = func_00120EB0(p->c, p->points);
        __asm__("qmtc2.ni %1,%0" : "=j"(b) : "r"(b));
        __asm__("qmtc2.ni %1, %0" : "=j"(h) : "r"(0.5f));
        __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(m) : "j"(a), "j"(h), "j"(b));
        __asm__("vsub.xyzw %0, %1, %0" : "+j"(a) : "j"(m));
        p->v100 = m;
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(a), "=&j"(one));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(a));
        *(int *)&p->g110 = g;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(b), "j"(D_00317570));
        { qword h2; __asm__("" : "=j"(h2) : "0"(h), "m"(p->g110)); u.q = h2; }
        p->x114 = func_00119C90(p->xDC, 0x7FFFFFFF, s) != 0;
    } else {
        p->g110 = D_00329530;
    }
}
