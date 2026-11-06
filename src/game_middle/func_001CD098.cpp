// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sphere against the BSP hull of a collision part (Sly 3 version of the Sly 2 CplaneFromSphere, src/hand/func_001A93C8.cpp): collects up to
// ccontactMax contacts of the sphere (pos, sRadius) with the first nodes of the part's BSP (pbspLimit) into acontact and returns their number.
//  1. No node list given: allocate min(cbspFull, 0x1555) nodes on the stack and prune the part's tree to the sphere (outside -> 0, wholly inside ->
//     the inside test of step 6, otherwise the written nodes with the last one as the root).
//  2. Every surface of the pruned tree is flagged 0x10.
//  3. Faces: the segment pos +- r*n is clipped to the tree; a piece that starts or ends on the surface itself is a face contact (kind 6, flag 0x80).
//  4. Edges: for each unflagged face, every edge whose neighbour face is flagged 0x10 (and not 0x80) gives the closest point to the sphere centre;
//     inside the radius an interior point is an edge contact (kind 5), a vertex becomes a candidate.
//  5. Vertex candidates that are not an end of one of the edge contacts become vertex contacts (kind 4).
//  6. The 0xF0 surface flags are cleared again; with no contact and the centre inside the hull the one contact comes from func_001CCDD8.
// Sly 3 differences from the Sly 2 source: the part (SOPART) refreshes its cached BSP / world geometry lazily (func_0018B1E0) before every access,
// and the normalize of the contact normal falls back to a fixed unit vector (D_00317530) for a degenerate length.
// Source-shape notes: the Sly 2 declaration order (vertex candidates at sp+0, then the stack frame scope), the function-level pbspNode / psurf /
// pcontact variables and the early-exit gotos are kept because they decide registers and spill slots; the vertex-contact loop takes the candidate
// address once (pv) so both of its loads share one address register.
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
typedef unsigned long    uint64_t;
typedef uint16_t    ushort;
typedef uint32_t    uint;
typedef uint64_t    ulong;
typedef unsigned long long qword __attribute__((mode(TI)));
struct VECTOR
{
    float x, y, z;
};
struct VECTOR4
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct VU_VECTOR4
{
    qword qw;
};
struct EDGE
{
    ushort aipos[2];
    ushort aisurf[2];
    EDGE *pedgeNext;
    EDGE *pedgeOtherNext;
};
struct SURF
{
    VECTOR normal;
    float gDot;
    EDGE *pedge;
    EDGE *pedgeOther;
    uint grf;
    int ipos;
};
struct GEOM
{
      int cpos;
      VECTOR *apos;
      int csurf;
      SURF *asurf;
      int cedge;
      EDGE *aedge;
};
enum LSGK
{
};
enum PRUNE
{
    PRUNE_Neg = 0,
    PRUNE_Pos = 1,
};
struct BSP
{
    BSP *pbspNeg;
    BSP *pbspPos;
    SURF *psurf;
};
struct BSPC
{
      int cbsp;
      int cbspFull;
      int nUnk08;
      BSP *absp;
};
struct LSG
{
      qword apos[2];
      qword anormal[2];
      float au[2];
      LSGK lsgk;
      SURF *apsurf[2];
      EDGE *pedge;
      int iiposSwap;
      LSG *plsgNext;
};
extern "C" int func_00119BE8(BSP *pbspRoot, BSP *pbspLimit, qword pos1, qword pos2, int clsgMax, LSG *alsg);
extern "C" PRUNE func_00119C20(BSP *pbsp, BSP *pbspLimit, qword pos, float sRadius, int *pcbspLeft, BSP **ppbspNext);
extern "C" BSP *func_00119CC8(BSP *pbsp, BSP *pbspLimit, qword pos);
struct CMCONTACT
{
      qword pos;
      qword plane;
      int kind;
      void *pv;
};
extern "C" void func_0018B1E0(void *p);
struct LOBJ { char pad0[0xA4]; int version; };
struct SOPART
{
    LOBJ *plo;                      // 0x00
    char pad04[0x78 - 4];
    BSPC bspc;                      // 0x78
    char pad88[0xA0 - 0x88];
    GEOM geomWorld;                 // 0xA0
    char padB8[0xC0 - 0xB8];
    int version;                    // 0xC0
};
static inline BSPC *Bspc(SOPART *p)
{
    if (p->version != p->plo->version)
        func_0018B1E0(p);
    return &p->bspc;
}
static inline GEOM *GeomWorld(SOPART *p)
{
    if (p->version != p->plo->version)
        func_0018B1E0(p);
    return &p->geomWorld;
}
struct SWALLOC
{
    int cb;
    int cbAlign;
};
extern "C" void *func_001D25B0(SWALLOC *pswalloc);
struct FRAME
{
    FRAME();
    ~FRAME();
};
struct VU_FLOAT
{
    qword qw;
};
static inline VU_FLOAT VuFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword qw2;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw2) : "j"(qw));
    return qw2;
}
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
extern qword D_00317530;
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword DivQ(qword qw, qword v)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(qw), "j"(v));
    return r;
}
static inline qword QwNormalize(qword v)
{
    qword qw = QwLength(v);
    qword fb = D_00317530;
    if (F(qw) < 1.0e-4f)
        return fb;
    return DivQ(qw, v);
}
extern "C" void func_00119EA8(SURF *psurf, qword qwNormal, qword qwPos);
extern "C" void func_001CCDD8(float sRadius, BSP *absp, BSP *pbspLimit, GEOM *pgeom, qword pos, CMCONTACT *pcontact);
struct VERTCAND
{
    int ivert;
    qword pos;
    qword plane;
};
static inline void *PvAllocStack(int cb)
{
    SWALLOC swalloc;
    swalloc.cb = cb;
    swalloc.cbAlign = 0x10;
    return func_001D25B0(&swalloc);
}
static inline qword QwAddScaled(qword qwBase, VU_FLOAT gScale, qword qwVec)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(qw) : "j"(qwBase), "j"(gScale.qw), "j"(qwVec));
    return qw;
}
static inline VU_VECTOR4 VecAddScaled(qword qwBase, VU_FLOAT gScale, qword qwVec)
{
    VU_VECTOR4 v;
    v.qw = QwAddScaled(qwBase, gScale, qwVec);
    return v;
}
int CplaneFromSphere(qword pos, float sRadius, SOPART *ppart, BSP *pbspLimit, int cbsp, BSP *absp, int ccontactMax, CMCONTACT *acontact) __asm__("func_001CD098");
int CplaneFromSphere(qword pos, float sRadius, SOPART *ppart, BSP *pbspLimit, int cbsp, BSP *absp, int ccontactMax, CMCONTACT *acontact)
{
    int ccontact;
    uint cvert;
    int ccontactFace;
    int ccontactEdge;
    BSP *pbsp;
    int cbspLeft;
    SURF *psurf;
    BSP *pbspNode;
    VU_VECTOR4 posContact;
    CMCONTACT *pcontact;
    GEOM *pgeom;
    VERTCAND avert[0x100];
    ccontact = cvert = 0;
    pgeom = GeomWorld(ppart);
    FRAME scope;
    if (ccontactMax > 0)
    {
        if (absp == 0)
        {
            BSPC *pbspc = Bspc(ppart);
            int cbspAlloc = 0x1555;
            if (pbspc->cbspFull < 0x1555)
                cbspAlloc = pbspc->cbspFull;
            cbspLeft = cbspAlloc;
            absp = (BSP *)PvAllocStack(cbspAlloc * sizeof(BSP));
            pbsp = absp;
            PRUNE prune = func_00119C20(pbspc->absp, pbspLimit, *(qword *)&pos, sRadius, &cbspLeft, &pbsp);
            if (prune == PRUNE_Neg)
                goto inside;
            if (prune == PRUNE_Pos)
                goto done;
            cbsp = pbsp - absp;
        }
        int i;
        pbsp = absp + (cbsp - 1);
        for (i = cbsp; --i >= 0; )
            absp[i].psurf->grf |= 0x10;
        for (i = cbsp; --i >= 0; )
        {
            pbspNode = &absp[i];
            psurf = pbspNode->psurf;
            if (psurf->grf & 0x10)
            {
                if (!(psurf->grf & 0x40))
                {
                    psurf->grf |= 0x40;
                    VECTOR4 vecA;
                    VECTOR4 vecB;
                    LSG alsg[16];
                    *(qword *)&vecA = QwAddScaled(pos, VuFloat(sRadius), *(qword *)pbspNode->psurf);
                    *(qword *)&vecB = QwAddScaled(pos, VuFloat(-sRadius), *(qword *)pbspNode->psurf);
                    int clsg = func_00119BE8(pbsp, (BSP *)0x7fffffff, *(qword *)&vecA, *(qword *)&vecB, 16, alsg);
                    int ilsg;
                    for (ilsg = 0; ilsg < clsg; ilsg++)
                    {
                        SURF *psurfHit;
                        if (1.0f < alsg[ilsg].au[0] + alsg[ilsg].au[1])
                            psurfHit = alsg[ilsg].apsurf[0];
                        else
                            psurfHit = alsg[ilsg].apsurf[1];
                        if (psurfHit == psurf)
                            break;
                    }
                    if (ilsg < clsg)
                    {
                        if (ccontact < ccontactMax)
                        {
                            pcontact = &acontact[ccontact++];
                            qword plane = *(qword *)psurf;
                            pcontact->kind = 6;
                            pcontact->plane = plane;
                            pcontact->pv = psurf;
                            *(VU_VECTOR4 *)&pcontact->pos = VecAddScaled(pos, VuFloat(-sRadius), plane);
                            if (ccontact >= ccontactMax)
                                goto clear;
                        }
                        psurf->grf |= 0x80;
                    }
                }
            }
        }
        ccontactFace = ccontact;
        for (i = cbsp; --i >= 0; )
        {
            VECTOR4 *apos = (VECTOR4 *)pgeom->apos;
            SURF *asurf = pgeom->asurf;
            pbspNode = &absp[i];
            psurf = pbspNode->psurf;
            if (psurf->grf & 0x10)
            {
                if (!(psurf->grf & 0xA0))
                {
                    psurf->grf |= 0x20;
                    for (EDGE *pedge = psurf->pedge; pedge != 0; pedge = pedge->pedgeNext)
                    {
                        SURF *psurfOther = &asurf[pedge->aisurf[1]];
                        if (!(psurfOther->grf & 0x10))
                            continue;
                        if (psurfOther->grf & 0x80)
                            continue;
                        VECTOR4 vecEdge;
                        VECTOR4 vecDelta;
                        VECTOR4 vecUnit;
                        VECTOR4 vecClosest;
                        VECTOR4 plane;
                        VECTOR4 *pposClosest = &apos[pedge->aipos[0]];
                        VECTOR4 *ppos1 = &apos[pedge->aipos[1]];
                        int ivert;
                        *(qword *)&vecEdge = QwSub(*(qword *)ppos1, *(qword *)pposClosest);
                        register int iLenSq __asm__("$3"); /* register pin: the edge length's int temp lives in $v1 like the original */
                        float gLenSq;
                        __asm__("qmfc2 %0, %1" : "=r"(iLenSq) : "j"(QwDot(*(qword *)&vecEdge, *(qword *)&vecEdge)));
                        __asm__("mtc1 %1, %0" : "=f"(gLenSq) : "r"(iLenSq));
                        *(qword *)&vecDelta = QwSub(pos, *(qword *)pposClosest);
                        float u = GFromVf(QwDot(*(qword *)&vecDelta, *(qword *)&vecEdge)) / gLenSq;
                        if (u < 0.0001f)
                        {
                            ivert = pedge->aipos[0];
                        }
                        else if (0.9999f < u)
                        {
                            pposClosest = ppos1;
                            ivert = pedge->aipos[1];
                            *(qword *)&vecDelta = QwSub(pos, *(qword *)pposClosest);
                        }
                        else
                        {
                            ivert = -1;
                            qword posBase = *(qword *)pposClosest;
                            *(qword *)&vecClosest = QwAddScaled(posBase, VuFloat(u), *(qword *)&vecEdge);
                            pposClosest = &vecClosest;
                            *(qword *)&vecDelta = QwSub(pos, *(qword *)&vecClosest);
                        }
                        u = GFromVf(QwDot(*(qword *)&vecDelta, *(qword *)&vecDelta));
                        if (u > sRadius * sRadius)
                            continue;
                        {
                            if (ivert >= 0)
                            {
                                for (int j = cvert - 1; j >= 0; j--)
                                    if (avert[j].ivert == ivert)
                                        goto nextedge;
                            }
                            *(qword *)&vecUnit = QwNormalize(*(qword *)&vecDelta);
                            func_00119EA8((SURF *)&plane, *(qword *)&vecUnit, *(qword *)pposClosest);
                            posContact = VecAddScaled(pos, VuFloat(-sRadius), *(qword *)&vecUnit);
                            if (ivert >= 0)
                            {
                                if (cvert < 0x100)
                                {
                                    VERTCAND *pvert = &avert[cvert++];
                                    pvert->ivert = ivert;
                                    pvert->pos = posContact.qw;
                                    pvert->plane = *(qword *)&plane;
                                }
                            }
                            else
                            {
                                if (ccontact >= ccontactMax)
                                    continue;
                                pcontact = &acontact[ccontact++];
                                *(VU_VECTOR4 *)&pcontact->pos = posContact;
                                pcontact->plane = *(qword *)&plane;
                                pcontact->kind = 5;
                                pcontact->pv = pedge;
                                if (ccontact >= ccontactMax)
                                    goto clear;
                            }
                        }
nextedge:
                        ;
                    }
                }
            }
        }
        ccontactEdge = ccontact;
        for (int iv = cvert - 1; iv >= 0; iv--)
        {
            int ivert = avert[iv].ivert;
            for (int j = ccontactFace; j < ccontactEdge; j++)
            {
                pcontact = &acontact[j];
                EDGE *pedge = (EDGE *)pcontact->pv;
                if (pedge->aipos[0] == ivert || pedge->aipos[1] == ivert)
                    goto nextvert;
            }
            if (ccontact < ccontactMax)
            {
                VERTCAND *pv = &avert[iv];
                pcontact = &acontact[ccontact++];
                pcontact->pos = pv->pos;
                pcontact->plane = pv->plane;
                pcontact->kind = 4;
                pcontact->pv = &((VECTOR4 *)pgeom->apos)[ivert];
                if (ccontact >= ccontactMax)
                    break;
            }
nextvert:
            ;
        }
clear:
        for (i = cbsp; --i >= 0; )
        {
            pbspNode = &absp[i];
            psurf = pbspNode->psurf;
            psurf->grf = (int)psurf->grf & ~0xF0;
        }
inside:
        if (ccontact == 0 && func_00119CC8(Bspc(ppart)->absp, pbspLimit, pos) != 0)
        {
            ccontact = 1;
            func_001CCDD8(sRadius, Bspc(ppart)->absp, pbspLimit, pgeom, pos, acontact);
        }
    }
done:
    return ccontact;
}
