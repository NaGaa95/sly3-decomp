// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00168358: point the object at the camera-space target of v (keep its current x rotation).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { qword r[4]; } q; M3 m3; float af[4][4]; } M4;
typedef union { qword q; float f[4]; } U;
struct LO;
typedef struct LOV { char pad[0x120]; short d; short p; M4 *(*pfnMat)(struct LO *); } LOV;
typedef struct LO { int a[3]; LOV *pvt; } LO;
struct CM;
qword func_001C9428(struct CM *p, int k, qword v);
qword func_0011D3C0(void *matrix);
void func_0011CBA0(M3 *matrix, qword dir);
void func_0011C9E8(M3 *matrix, qword angles);
qword *func_002BA818(qword *out, qword value);
void func_00166DE8(LO *p, M4 *matrix);
static __inline__ M4 *VMat(LO *plo) { return plo->pvt->pfnMat((LO *)((char *)plo + plo->pvt->d)); }
void func_00168358(LO *p, struct CM *pcm, qword v)
{
    U pos, eul, t, eul2;
    M4 m4;
    M3 m;
    qword d;
    if (!pcm)
        return;
    pos.q = VMat(p)->q.r[3];
    eul.q = func_0011D3C0(VMat(p));
    t.q = func_001C9428(pcm, 0, v);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(t.q), "j"(pos.q));
    func_0011CBA0(&m, d);
    eul2.q = func_0011D3C0(&m);
    eul.f[1] = eul2.f[1];
    eul.f[2] = eul2.f[2];
    func_0011C9E8(&m, eul.q);
    {
        M4 *pm4 = &m4;
        func_002BA818(&pm4->q.r[3], pos.q);
        pm4->q.r[0] = m.r[0];
        pm4->q.r[1] = m.r[1];
        pm4->q.r[2] = m.r[2];
        m4.af[2][3] = 0.0f;
        m4.af[1][3] = 0.0f;
        m4.af[0][3] = 0.0f;
        pm4->af[3][3] = 1.0f;
        func_00166DE8(p, pm4);
    }
}
