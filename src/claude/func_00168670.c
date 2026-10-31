// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct CLOCK { float t; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct OBJ { char pad[0xC]; struct VEntry *table; char pad10[0x130 - 0x10]; int k130; char pad134[0x148 - 0x134];
    struct OBJ *p148; char pad14C[0x1A0 - 0x14C]; int grf1A0; };
struct ST { char pad[0xC]; struct VEntry *table; char pad10[0x440 - 0x10]; int c440; float t444; };
struct GAME { char pad[0x4F48]; float t4F48; };
struct Q { char pad[0x164]; int grf164; };
struct R { char pad[8]; float g8; };
extern struct CLOCK g_clock;
extern struct GAME D_00475480;
extern char D_0036C700[];
extern char D_0046FC90[];
extern struct VQ { qword q; } D_00317550;
void func_001854C8(void *p, int n, struct ST *pst);
int func_0017E208(void *pv, int a, int b, int c, int cMax, struct OBJ **apobj);
struct Q *func_00166540(struct ST *p);
int func_00282750(struct OBJ *p);
void func_00281E70(struct OBJ *p);
void func_00281F98(struct OBJ *p);
int func_00282870(struct OBJ *p, struct ST *pst, float *pg, int a, int b);
struct R *func_00281E28(struct OBJ *p, struct ST *pst);
void func_00222C50(void *pv, struct ST *pst, qword pos, struct OBJ *pobj, qword v);
#define GETPOS(o) (*(qword *)((char *)(o)->table[36].get((char *)(o) + (o)->table[36].delta) + 0x30))
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ qword Len(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    return d;
}
static __inline__ float GetX(qword v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
void func_00168670(struct ST *p, int k)
{
    D_00475480.t4F48 = g_clock.t;
    p->t444 = g_clock.t;
    switch (k) {
    case 1:
        p->c440++;
        break;
    case 2:
        break;
    case 0: {
        struct OBJ *apobj[0x10];
        int c, i;
        int grf = 0xFF;
        struct Q *pq;
        struct OBJ *pobjBest, *pobjCur, **pp;
        float gBest, gCur, dMin, g;
        qword pos;

        p->c440++;
        func_001854C8(D_0036C700, 0x4F, p);
        c = func_0017E208(&D_00475480, 0x105, 0x78, 0, 0x10, apobj);
        pq = func_00166540(p);
        if (pq)
            grf = pq->grf164;
        pobjCur = 0;
        gBest = 1.0f;
        pobjBest = 0;
        pos = GETPOS(p);
        dMin = 3.402823466e+38f;
        for (i = 0; i < c; i++) {
            struct OBJ *pobj = apobj[i];
            int r;
            if (!func_00282750(pobj))
                continue;
            if (!(grf & pobj->grf1A0))
                continue;
            switch (pobj->k130) {
            case 2:
                continue;
            case -1:
                pobjCur = pobj;
                break;
            case 0:
            case 1:
                break;
            }
            func_00281E70(pobj);
            func_00281F98(pobj);
            r = func_00282870(pobj, p, &g, 0, 0);
            if (pobj == pobjCur) {
                if (!r)
                    pobjCur = 0;
                else
                    gCur = g;
                continue;
            }
            if (!r)
                continue;
            {
                float d = GetX(Len(Sub(pos, GETPOS(pobj))));
                if (d < dMin) {
                    gBest = g;
                    pobjBest = pobj;
                    dMin = d;
                }
            }
        }
        if (!pobjBest && pobjCur) {
            pobjBest = pobjCur;
            gBest = gCur;
        }
        if (pobjBest) {
            struct R *pr = func_00281E28(pobjBest, p);
            struct OBJ *pt = pobjBest->p148 ? pobjBest->p148 : pobjBest;
            float h = pr->g8 + gBest * 300.0f;
            U s;
            qword rs, v;
            __asm__("qmtc2.ni %1, %0" : "=j"(rs) : "r"(h));
            s.q = rs;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v) : "j"(D_00317550.q), "j"(rs));
            func_00222C50(D_0046FC90, p, pos, pt, v);
        }
        break;
    }
    }
}
