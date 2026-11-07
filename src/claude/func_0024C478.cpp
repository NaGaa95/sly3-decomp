// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0024C478: pick the nearest visible target in front of the camera (cf. Sly 2 func_002026F8), Sly 3 layout:
// positions through the objects' vtables, the camera from func_001F4A80.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("lw %0, %1" : "=rj"(q) : "m"(f)); } };
struct VTE { short delta; short pad; void *pfn; };
struct POSO { char pad[0x30]; qword pos; };
struct O
{
    char pad0[0xC];
    VTE *vt;
    char pad10[0x24];
    float height;
    char pad38[0xD0 - 0x38];
    float radius;
    char padD4[0xF8 - 0xD4];
    int state;
};
struct OWNER { O *po; };
struct P
{
    char pad0[0x20];
    qword pos;
    int cpo;
    O *apo[0x16];
    O *poBest;
    char pad90[0xA8 - 0x90];
    OWNER *powner;
};
extern "C" {
O *func_001F4A80(O *po);
int func_0024D6E8(O *po);
int func_00167F60(O *pcm, qword pos, VU_FLOAT g);
int func_00168048(O *pcm, qword pos, float g, void *p);
void func_0024C288(P *p, O *po);
void func_0024C6D8(P *p, int n);
}
static inline POSO *Poso(O *po)
{
    VTE *e = &po->vt[0x24];
    return ((POSO *(*)(void *))e->pfn)((char *)po + e->delta);
}
static inline float LengthXY(qword a, qword b)
{
    qword d;
    float g;
    int t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    __asm__("qmfc2.ni %1, %2\n\tmtc1 %1, %0" : "=f"(g), "=&r"(t) : "j"(d));
    return g;
}

extern "C" void func_0024C478(P *p)
{
    O *poBest = 0;
    int i = 0;
    O *pcm = func_001F4A80(p->powner->po);
    float gMin;
    qword apos[8];
    {
        O *po = p->powner->po;
        VTE *e = &po->vt[0x55];
        ((void (*)(void *, qword *))e->pfn)((char *)po + e->delta, apos);
        p->pos = apos[0];
    }
    ((float *)&p->pos)[2] += 20.0f;
    gMin = 3.40282347e+38f;
    for (; i < p->cpo; i++)
    {
        O *po = p->apo[i];
        if (!func_0024D6E8(po))
            continue;
        if (!func_00167F60(pcm, Poso(po)->pos, VU_FLOAT(po->radius)))
            continue;
        if (!func_00168048(pcm, Poso(po)->pos, po->height, 0))
            continue;
        qword posO = Poso(po)->pos;
        qword posC = Poso(pcm)->pos;
        __asm__("" : : "j"(posO)); // zero-instruction: allocation priority for posO (vf1)
        float g = LengthXY(posO, posC);
        if (g < gMin)
        {
            func_0024C288(p, po);
            if (po->state != 2)
            {
                poBest = po;
                gMin = g;
            }
        }
    }
    if (poBest != p->poBest)
    {
        p->poBest = poBest;
        func_0024C6D8(p, 2);
    }
}
