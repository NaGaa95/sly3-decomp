// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct LM { float gMin, gMax; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct OBJ { char pad[0xC]; struct VEntry *table; char pad10[0x2F0 - 0x10]; int k2F0; };
struct G { char pad[0xC]; struct VEntry *table; char pad10[0x17F8 - 0x10]; int c17F8; struct OBJ *a17FC[0x20]; char pad187C[0x187C - 0x187C]; float g187C; };
struct ST { char pad[0x10]; struct G *pg; char pad14[0x40 - 0x14]; int k40; };
static const struct LM D_00320B28 = { -0.4f, 0.4f };
static const struct LM D_00320B30 = { -0.4f, 0.4f };
static const struct LM D_00320B38 = { -0.3f, 0.3f };
static const struct LM D_00320B40 = { -0.2f, 0.2f };
extern char D_00475480[];
int func_001C8610(struct OBJ *p);
int func_0017E208(void *pv, int a, int b, int c, int cMax, struct OBJ **apobj);
int func_0013B500(struct OBJ *p, int n);
float atan2f(float y, float x);
void *func_001F4A80(struct G *p);
void func_00120BA8(qword v, float *pa, float *pb, float *pc);
qword func_001678C8(void *p, qword v);
int func_0011EE30(const struct LM *plm, float g);
float func_0011E3B8(float g);
#define GETPOS(o) (*(qword *)((char *)(o)->table[36].get((char *)(o) + (o)->table[36].delta) + 0x30))
#define MATRIX(o) ((float *)(o)->table[36].get((char *)(o) + (o)->table[36].delta))
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ float PackedX(qword v) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(v)); return g; }
static __inline__ float PackedY(qword v) { float g; __asm__("prot3w %0, %1" : "=r"(g) : "r"(v)); return g; }
static __inline__ float PackedZ(qword v) { float g; __asm__("pextuw %0, $0, %1" : "=r"(g) : "r"(v)); return g; }
struct OBJ *func_00161720(struct ST *p)
{
    struct OBJ *apobj[0x20];
    struct OBJ *apobjFound[0x20];
    int c = 0;
    struct OBJ *pobjBest = 0;
    int i;
    int k;
    float gMax, gYaw;
    float f[3];
    qword pos;
    void *pv;

    if (p->pg->c17F8) {
        for (i = 0; i < p->pg->c17F8; i++) {
            struct OBJ *pobj = p->pg->a17FC[i];
            if (func_001C8610(pobj))
                apobj[c++] = pobj;
        }
    } else {
        int j;
        int cFound = func_0017E208(D_00475480, 0x105, 0x32, 0, 0x20, apobjFound);
        for (j = 0; j < cFound; j++) {
            struct OBJ *pobj = apobjFound[j];
            if (pobj == (struct OBJ *)p->pg)
                continue;
            if (func_0013B500(pobj, 0x3A) && pobj->k2F0 == 2)
                continue;
            apobj[c++] = pobj;
        }
    }
    gMax = p->pg->g187C;
    pos = GETPOS(p->pg);
    {
        float *pm = MATRIX(p->pg);
        gYaw = atan2f(pm[1], pm[0]);
    }
    pv = func_001F4A80(p->pg);
    for (k = 0; k < c; k++) {
        struct OBJ *pobj = apobj[k];
        qword v = GETPOS(pobj);
        func_00120BA8(Sub(v, pos), &f[0], &f[1], &f[2]);
        if (gMax < f[2])
            continue;
        if (f[2] < 150.0f)
            continue;
        if (p->k40 == 1) {
            qword q = func_001678C8(pv, v);
            if (PackedZ(q) < 0.0f)
                continue;
            if (!func_0011EE30(&D_00320B28, PackedX(q)))
                continue;
            if (!func_0011EE30(&D_00320B30, PackedY(q)))
                continue;
        } else {
            if (!func_0011EE30(&D_00320B38, f[1]))
                continue;
            {
                float h = func_0011E3B8(f[0] - gYaw);
                if (!func_0011EE30(&D_00320B40, h))
                    continue;
            }
        }
        gMax = f[2];
        pobjBest = pobj;
    }
    return pobjBest;
}
