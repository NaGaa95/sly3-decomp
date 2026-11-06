// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-strength-reduce
// Emitter point/direction generator: fills out->apos (and out->advs) with out->count entries according to the emitter
// shape: 0 = the fixed point, 1 = random point in a box, 2 = point (and direction, kindDir 2/3) on a mesh by stratified
// area sampling, 3 = random triangle (area weighted) and barycentric point, normal direction when kindDir == 5.
// Port of the Sly 2 version func_0015A808 (which handled one entry at a time), same helpers.
// Matching notes: the empty block in case 1 mirrors the unused 48-byte local of the Sly 2 source (its stack slot is
// reused by case 3's an[]); `i * 16 + (long)out->apos` keeps the scaled index as the first addend; ctri is read once.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; };
struct TRI { int aipos[3]; float sArea; };
struct EMITMESH { int cpos; qword *apos; int ctri; TRI *atri; qword *anormal; float sArea; };
struct BOXE { float xMin, yMin, zMin, pad; float xMax, yMax, zMax; };
struct MESHO { char pad[0xD8]; int cs; int padDC; float *as; };
struct EP { char pad0[0x30]; qword v30; char pad40[8]; int kind; int kindDir; };
struct EMIT { char pad0[4]; struct { char pad[0x10]; EP *pep; } *pdata; MESHO *pmesh; };
struct OUT { int count; qword *apos; qword *advs; };
extern qword D_00317530;
extern "C" {
float func_0011E940(float gMin, float gMax);
void func_0022E4D0(MESHO *pmesh, qword *ppos, qword *pdir, float g);
void *func_00292034(void *, int, int);
}
static inline qword Cross(qword a, qword b)
{
    qword d;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
static inline qword Combo3(VU_FLOAT f0, VU_VECTOR v0, VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword d;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddax.xyzw $ACC, %4, %3x\n\tvmaddx.xyzw %0, %6, %5x"
            : "=j"(d) : "j"(f0.q), "j"(v0.q), "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return d;
}
static inline qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=&j"(l) : "j"(c));
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(l));
    return r;
}
static inline float GFromQw(qword q) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(q)); return g; }
static inline VU_VECTOR Normalize(qword d)
{
    VU_VECTOR dir;
    qword l = VLen(d);
    qword k = D_00317530;
    if (GFromQw(l) < 0.0001f) {
        dir.q = k;
    } else {
        qword dq;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(dq) : "j"(d), "j"(l));
        dir.q = dq;
    }
    return dir;
}
extern "C" void func_001FF6B0(EMIT *p, OUT *out)
{
    EP *ep = p->pdata->pep;
    VU_VECTOR av[3];
    switch (ep->kind) {
    case 0:
        for (int i = 0; i < out->count; i++)
            out->apos[i] = *(qword *)ep;
        break;
    case 1: {
        { VU_VECTOR avUnused[3]; }
        BOXE *pbox = (BOXE *)ep;
        for (int i = 0; i < out->count; i++) {
            float x = func_0011E940(pbox->xMin, pbox->xMax);
            float y = func_0011E940(pbox->yMin, pbox->yMax);
            float z = func_0011E940(pbox->zMin, pbox->zMax);
            float *pf = (float *)(i * 16 + (long)out->apos);
            pf[0] = x;
            pf[1] = y;
            pf[2] = z;
        }
        break;
    }
    case 2: {
        MESHO *pmesh = p->pmesh;
        if (!pmesh) {
            func_00292034(out->apos, 0, out->count << 4);
            break;
        }
        float ds = pmesh->as[pmesh->cs - 1] / (float)out->count;
        float s = 0.0f;
        switch (ep->kindDir) {
        case 2:
            for (int i = 0; i < out->count; i++) {
                float e = s + ds;
                float g = func_0011E940(s, e);
                func_0022E4D0(p->pmesh, &out->apos[i], &out->advs[i], g);
                s = e;
            }
            break;
        case 3:
            for (int i = 0; i < out->count; i++) {
                float e = s + ds;
                float g = func_0011E940(s, e);
                func_0022E4D0(p->pmesh, &out->apos[i], &out->advs[i], g);
                out->advs[i] = Normalize(Cross(out->advs[i], ep->v30)).q;
                s = e;
            }
            break;
        default:
            for (int i = 0; i < out->count; i++) {
                float e = s + ds;
                float g = func_0011E940(s, e);
                func_0022E4D0(p->pmesh, &out->apos[i], 0, g);
                s = e;
            }
            break;
        }
        break;
    }
    case 3:
        for (int i = 0; i < out->count; i++) {
            EMITMESH *pem = (EMITMESH *)ep;
            float s = func_0011E940(0.0f, 1.0f) * pem->sArea;
            TRI *ptri;
            int itri;
            int ctri = pem->ctri;
            for (itri = 0; itri < ctri; itri++) {
                ptri = &pem->atri[itri];
                s -= ptri->sArea;
                if (s <= 0.0f)
                    break;
            }
            av[0].q = pem->apos[ptri->aipos[0]];
            av[1].q = pem->apos[ptri->aipos[1]];
            av[2].q = pem->apos[ptri->aipos[2]];
            float u = func_0011E940(0.0f, 1.0f);
            float v = func_0011E940(0.0f, 1.0f - u);
            float w = 1.0f - u - v;
            out->apos[i] = Combo3(u, av[0], v, av[1], w, av[2]);
            if (ep->kindDir == 5) {
                VU_VECTOR an[3];
                an[0].q = pem->anormal[ptri->aipos[0]];
                an[1].q = pem->anormal[ptri->aipos[1]];
                an[2].q = pem->anormal[ptri->aipos[2]];
                out->advs[i] = Normalize(Combo3(u, an[0], v, an[1], w, an[2])).q;
            }
        }
        break;
    }
}
