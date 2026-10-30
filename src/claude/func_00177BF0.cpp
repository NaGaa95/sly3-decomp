// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/ModifyEmitterParticles__FP7EMITTER.cpp (offsets shifted, ALO position via vtable slot, scoped local with dtor func_002BC3D8).
typedef int qword __attribute__((mode(TI)));
union V { qword q; struct { float x, y, z, w; } v; float a[4]; };
struct BLK { qword apos[2][0x84]; int ibuf; int cpart; int pad[2]; BLK *pblkNext; };
struct PRG { char pad[0x438]; BLK *pblkFirst; };
struct VEntry { short delta; short pad; void *(*get)(void *); };
struct ALO { char pad[0xC]; VEntry *table; };
#define GETPOS(o) (*(qword *)((char *)(o)->table[36].get((char *)(o) + (o)->table[36].delta) + 0x30))
struct EMITO { ALO *palo; };
struct EMITB { int pad0; int f4; EMITO *pemito; };
struct EMITTER { char pad[0xD4]; EMITB *pemitb; char pad1[0x11C - 0xD8]; float sBox; char pad2[0x12C - 0x120]; PRG *pprg; };
extern "C" {
void func_002BC3D8(void *object, int flags);
float func_0011EDB8(float g, float gMod);
}
static inline qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline void Wrap(float *pg, float &gMin, float &gMax, float &gBox, float *pdg)
{
    if (*pg < gMin || gMax < *pg) {
        *pdg = gMin + func_0011EDB8(*pg - gMin, gBox) - *pg;
        *pg += *pdg;
    }
}
struct SCOPE {
    qword pad;
    ~SCOPE() { func_002BC3D8(this, 2); }
};
extern "C" void func_00177BF0(EMITTER *pemitter)
{
    float sBox = pemitter->sBox;
    if (sBox > 0.0001f) {
        V vecBox, posMin, posMax, dpos;
        vecBox.v.z = sBox; vecBox.v.y = sBox; vecBox.v.x = sBox;
        if (pemitter->pemitb->pemito->palo) {
            posMin.q = Sub(GETPOS(pemitter->pemitb->pemito->palo), vecBox.q);
            posMax.q = Add(GETPOS(pemitter->pemitb->pemito->palo), vecBox.q);
        } else {
            qword m, k;
            __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(-1.0f));
            dpos.q = k;
            __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(m) : "j"(vecBox.q), "j"(k));
            posMin.q = m;
            posMax.q = vecBox.q;
        }
        float sBox2 = pemitter->sBox + pemitter->sBox;
        vecBox.v.z = sBox2; vecBox.v.y = sBox2; vecBox.v.x = sBox2;
        if (pemitter->pemitb->f4 == 0 && pemitter->pprg) {
            SCOPE scope;
            for (BLK *pblk = pemitter->pprg->pblkFirst; pblk; pblk = pblk->pblkNext) {
                qword *apos = pblk->apos[pblk->ibuf];
                for (int i = 0; i < pblk->cpart; i++) {
                    V *ppos = (V *)&apos[i];
                    Wrap(&ppos->v.x, posMin.v.x, posMax.v.x, vecBox.v.x, &dpos.v.x);
                    Wrap(&ppos->v.y, posMin.v.y, posMax.v.y, vecBox.v.y, &dpos.v.y);
                    Wrap(&ppos->v.z, posMin.v.z, posMax.v.z, vecBox.v.z, &dpos.v.z);
                }
            }
        }
    }
}
