// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001E6830: clips the segment pos1-pos2 to the convex volume pcnvo (its cplane - 1 planes, built by func_001E75F0)
// and writes the parts of it OUTSIDE the volume to alsg (at most clsgMax LSGs); returns how many. Convex-volume twin of
// the Sly 2 routine func_001BC688 (same LSG record, 0x60 bytes: apos[2], anormal[2], au[2], apsurf[2]); the Sly 3 version
// tests each endpoint against a +-1 unit band around the plane instead of adding a bias.
// gIn / gOut = where the segment enters / leaves the volume (0 = pos1, 1 = pos2), normalIn / normalOut = those planes.
// If the segment never enters (gOut <= gIn) it is emitted whole; else [0, gIn] and [gOut, 1] are emitted with the
// negated plane normal at the cut.
// Allocation notes:
// - VU_QWORD() is the out-of-line constructor func_002BA000; every dot product lives in constructed VU_QWORD temporaries.
// - the plane is kept in a VU_VECTOR copy (inline ctor taking a const qword &), otherwise cse propagates the register copy away.
// - GXOfQw: the qmfc2 after the 2nd dot product is a compiler move and the mtc1 is asm. Its extra "j" inputs are
//   allocation-only: the duplicate "j"(vf) keeps dot2 VU-class (else it is stored with sq), the two "j"(vfLive) raise
//   vfOne2's local-alloc priority so it gets vf1 like vfOne1.
typedef int qword __attribute__((mode(TI)));
struct VU_QWORD { qword qw; VU_QWORD() __asm__("func_002BA000"); };
struct VU_FLOAT { qword qw; };
struct VU_VECTOR { qword qw; VU_VECTOR(const qword &q) { qw = q; } };
struct LSG {
    qword apos[2];
    qword anormal[2];
    float au[2];
    int lsgk;
    void *apsurf[2];
    void *pedge;
    int iiposSwap;
    LSG *plsgNext;
};
struct CNVO { char pad[0xD8]; int cplane; char pad2[0x1DC - 0xDC]; qword *aplane; };
extern "C" {
void func_001E75F0(CNVO *p);
void *memset(void *, int, unsigned) __asm__("func_00292034");
}
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GXOfQw(const VU_QWORD &vf, const VU_QWORD &vfLive)
{
    float g;
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(vf.qw), "j"(vf.qw), "j"(vfLive.qw), "j"(vfLive.qw)); /* "j" inputs: allocation only (see header) */
    return g;
}
static inline qword QwMix(VU_FLOAT g1, const qword &qw1, VU_FLOAT g2, const qword &qw2)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %4x" : "=j"(qw) : "j"(qw1), "j"(qw2), "j"(g1.qw), "j"(g2.qw));
    return qw;
}
static inline qword QwZero() { qword qw; __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(qw)); return qw; }
static inline qword QwNeg(qword v) { qword qw; __asm__("vsub.xyzw %0, $vf0, $vf0\n\tvsub.xyzw %0, %0, %1" : "=&j"(qw) : "j"(v)); return qw; }

extern "C" int func_001E6830(CNVO *pcnvo, qword pos1, qword pos2, int clsgMax, LSG *alsg)
{
    func_001E75F0(pcnvo);
    float gIn = 0.0f;
    qword normalIn = QwZero();
    float gOut = 1.0f;
    qword normalOut = normalIn;
    int i;
    for (i = 0; i < pcnvo->cplane - 1; i++) {
        qword plane = pcnvo->aplane[i];
        VU_VECTOR normal(plane);
        VU_QWORD dot1;
        VU_QWORD vfOne1;
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
                : "=j"(dot1), "=j"(vfOne1) : "j"(plane), "j"(pos1));
        float g1 = GFromVf(dot1.qw);
        VU_QWORD dot2;
        VU_QWORD vfOne2;
        __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
                : "=j"(vfOne2), "=j"(dot2) : "j"(plane), "j"(pos2));
        float g2 = GXOfQw(dot2, vfOne2);
        int inside1 = g1 < -1.0f;
        int outside1 = 1.0f < g1;
        int inside2 = g2 < -1.0f;
        int outside2 = 1.0f < g2;
        if ((inside1 && outside2) || (outside1 && inside2)) {
            float t = g1 / (g1 - g2);
            if (g1 < 0.0f) {
                if (t < gOut) {
                    gOut = t;
                    normalOut = plane;
                }
            } else {
                if (gIn < t) {
                    gIn = t;
                    normalIn = plane;
                }
            }
            if (gOut <= gIn)
                break;
        } else if (!inside1) {
            if (!inside2) {
                gIn = gOut = 0.0f;
                break;
            }
        }
    }
    int clsg = 0;
    LSG *plsg;
    if (gOut <= gIn && clsg < clsgMax) {
        plsg = &alsg[clsg++];
        memset(plsg, 0, sizeof(LSG));
        plsg->apos[0] = pos1;
        plsg->au[1] = 1.0f;
        plsg->apos[1] = pos2;
        plsg->au[0] = 0.0f;
    } else {
        if (gIn > 0.0f && clsg < clsgMax) {
            plsg = &alsg[clsg++];
            memset(plsg, 0, sizeof(LSG));
            plsg->apos[0] = pos1;
            plsg->apos[1] = QwMix(VuFloat(1.0f - gIn), pos1, VuFloat(gIn), pos2);
            plsg->anormal[1] = QwNeg(normalIn);
            plsg->au[0] = 0.0f;
            plsg->au[1] = gIn;
            plsg->apsurf[1] = pcnvo;
        }
        if (gOut < 1.0f && clsg < clsgMax) {
            plsg = &alsg[clsg++];
            memset(plsg, 0, sizeof(LSG));
            plsg->apos[0] = QwMix(VuFloat(1.0f - gOut), pos1, VuFloat(gOut), pos2);
            plsg->anormal[0] = QwNeg(normalOut);
            plsg->apos[1] = pos2;
            plsg->au[0] = gOut;
            plsg->au[1] = 1.0f;
            plsg->apsurf[0] = pcnvo;
        }
    }
    return clsg;
}
