// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0026F190: Sly 3 form of Sly 2 UpdateChainLink (func_0021CB18, src/hand/func_0021CB18.cpp in the Sly 2 decomp), the
// chain-link update called by role 0x11 of UpdateSoSlots (func_0028CA78). Ported from the Sly 2 source; Sly 3 differences:
//  - before simulating, every link before this one, every dirty link (fDirty at +0x68) and every link when the SO's flag 0x10 is set is
//    re-read from its XF (and its dirty flag cleared), in one loop;
//  - a link after the first starts from the tip of the link before and the direction of that link's rest segment in its XF's world matrix
//    (Sly 2: the parent XF's position) when it is the second link; a bend clamp also clamps the angle used by the bend pull;
//  - returns 1 unless the simulation ran and moved no tip by more than 0.1 (squared distance 0.01): UpdateSoSlots keeps the SO awake.
// Matching notes (Sly 3): the anchor's dt is read through an inline taking &g_clock (keeps hi(g_clock) shared with the t test only);
// qwVelTip is declared before posBase and qwD before the other loop qwords (spill-slot order), the integrated velocities / tip are new
// variables (qwVelNew, qwVelOut, qwTipOut), QwChainVel's dt has one allocation-only "j" operand (local-alloc order vf4/vf5), and the
// second link's rest segment is read through a pointer.
typedef unsigned char    uint8_t;
typedef unsigned int     uint32_t;
typedef unsigned long    uint64_t;
typedef uint8_t     uchar;
typedef uint32_t    uint;
typedef uint64_t    ulong;
typedef uchar   undefined1;
typedef uint    undefined4;
typedef unsigned long long qword __attribute__((mode(TI)));
typedef uchar byte;
enum MSGID
{
};
struct LO;
struct RGBA
{
    uchar bRed;
    uchar bGreen;
    uchar bBlue;
    uchar bAlpha;
    inline void operator=(const int rgba)
    {
        bRed = (rgba >> 24) & 0xFF;
        bGreen = (rgba >> 16) & 0xFF;
        bBlue = (rgba >> 8) & 0xFF;
        bAlpha = rgba & 0xFF;
    }
};
struct SO;
struct VECTOR
{
    float x, y, z;
};
struct VECTOR4
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct MATRIX4
{
	float mat[4][4];
} __attribute__((aligned(16)));
struct MATRIX3
{
	float mat[3][4];
} __attribute__((aligned(16)));
struct VU_VECTOR4
{
    qword qw;
};
inline MATRIX3 operator*(const MATRIX3 &matL, const MATRIX3 &matR) return mat
{
    qword qwL0 = *(qword *)matL.mat[0];
    qword qwL1 = *(qword *)matL.mat[1];
    qword qwL2 = *(qword *)matL.mat[2];
    VU_VECTOR4 v0;
    VU_VECTOR4 v1;
    VU_VECTOR4 v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[0])->qw));
    *(VU_VECTOR4 *)mat.mat[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[1])->qw));
    *(VU_VECTOR4 *)mat.mat[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(((VU_VECTOR4 *)matR.mat[2])->qw));
    *(VU_VECTOR4 *)mat.mat[2] = v2;
}
inline qword QwRotateVec(MATRIX3 *pmat, qword qwVec)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(qwResult)
            : "j"(*(qword *)pmat->mat[0]), "j"(*(qword *)pmat->mat[1]), "j"(*(qword *)pmat->mat[2]), "j"(qwVec));
    return qwResult;
}
MATRIX3 BuildRotateVectorsMatrix(qword vec1, qword vec2) __asm__("func_0011CDC8");
enum OID
{
};
struct SL
{
    void *head;
    void *tail;
    int ibSle;
};
struct SLE
{
    void *next;
};
struct DL
{
    void *head;
    void *tail;
    int ibDle;
};
struct DLE
{
    void *next;
    void *prev;
};
struct XF;
struct ACT
{
      int ack;
      SO *pso;
      XF *pxf;
      int nPriority;
      ACT *pactNext;
      int nRole;
    ACT() {}
    ACT(int ack) : ack(ack) {}
};
template <class T>
class CRefPtr
{
public:
    T *m_p;
    CRefPtr() {}
    CRefPtr(T *p) { Attach(p); }
    CRefPtr(const CRefPtr &ref)
    {
        m_p = ref.m_p;
        if (m_p)
        {
            m_p->m_cref++;
        }
    }
    ~CRefPtr()
    {
        if (m_p)
        {
            m_p->Release();
        }
    }
    void operator=(T *p);
    void operator=(const CRefPtr &ref) { *this = ref.m_p; }
    operator T *() { return m_p; }
    T *operator->() { return m_p; }
};
class CSidebag;
class CFrame;
struct BASIC
{
      CRefPtr<CFrame> pframe;
      CRefPtr<CSidebag> psidebag;
      struct REFNODE *prefnodeFirst;
      virtual void SendMessage(MSGID msgid, void *pv);
};
struct PXR;
struct LOROOT
{
      LO *plo;
      DLE dle;
      DLE dleBusy;
};
struct LORUN
{
      void *pv;
      LORUN *plorunNext;
};
struct LO : public BASIC
{
      SO *psoParent;
      LOROOT *ploroot;
      OID oid;
      SLE sleOid;
      SLE sleCid;
      DLE dleChild;
      char cpaloFindSwObjects;
      uchar grfvis;
      long nUnk48 : 4;
               long busyk : 4;
               ulong fRemoved : 1;
               ulong fUnk57 : 1;
               ulong fUnk58 : 1;
               ulong fUnk59 : 1;
               ulong fInWorld : 1;
      float gUnk30;
      LORUN *plorunFirst;
      PXR *ppxr;
      int grfUnk40;
};
struct CLQ
{
    union
    {
        struct
        {
            float g0, g1, g2, gUnused;
        };
        float ag[4];
    };
};
struct LM
{
	float gMin, gMax;
};
typedef ulong TICK;
enum CRK
{
    CRK_Max = 9
};
struct CLOCK
{
      float t;
      float dt;
      float rt;
      float rtCm;
      float dtCm;
      float tCm;
      float art[CRK_Max];
      float tReal;
      float dtReal;
      undefined4 unk_0x44;
      TICK tickFrame;
      TICK tickLastRaw;
      int cWrapAround;
      undefined4 unk_0x5c;
};
extern CLOCK g_clock;
struct SOPART;
struct BND;
struct WRBG;
struct GLOB
{
      OID oid;
      XF *pxf;
      MATRIX4 *pmatUnk08;
      union
    {
        uint grf;
        struct
        {
            uint grfglobType : 3;
            uint iUnk0c3 : 5;
            uint unk_0x0d : 2;
            uint fLimit : 1;
            uint fHide : 1;
            uint fBakedMat : 1;
            uint iUnkFirst : 9;
            uint iUnkEnd : 9;
            uint unk_0x1f : 1;
        };
    };
      void *pvUnk10;
      void *pvUnk14;
      BND *abnd;
      WRBG *pwrbg;
      struct SAA *psaa;
      struct POSE *ppose;
};
struct SUBGLOB
{
      char bUnk00;
      char cbnd;
      int bUnk02 : 8;
      char type;
      float gUnk04;
      void *pvLit;
      int iqwBone;
      int cqw;
};
struct SUBGLOBX
{
      VECTOR posCenter;
      float sRadius;
      float gUnk10;
      uint grfUnk14;
};
struct POSE
{
      VECTOR pos;
      float gUnk0c;
      float gUnk10;
      long nKind : 4;
    ulong ucUnk : 8;
    ulong ibUnk : 6;
    ulong fHide : 1;
    long iglob : 13;
      void *pvUnk18;
      undefined4 unk_0x1c;
};
struct POSESET
{
    POSE apose[4];
};
struct GLOBSET
{
      SO *pso;
      float tUnk04;
      undefined4 unk_0x08[2];
      VECTOR posCenter;
      undefined4 unk_0x1c;
      float sRadius;
      int cpsaa;
      SAA **apsaa;
      int cnUnk2c;
      int *anUnk30;
      int nUnk34;
      int cglob;
      SUBGLOB *asubglob;
      GLOB *aglob;
      SUBGLOBX *asubglobx;
      POSESET *aposeset;
      int nUnk4c;
      union
    {
        float gUnk50;
        struct
        {
            ulong unk_0x50 : 32;
            ulong fBoundsUnk32 : 1;
            ulong fBoundsUnk33 : 1;
            ulong fUnk34 : 1;
            ulong unk_0x54 : 29;
        };
    };
      WRBG *pwrbgFirst;
      void *pbatchrecsFirst;
};
struct XF
{
      MATRIX4 mat;
      MATRIX4 matWorld;
      float gUnk80;
      float gUnk84;
      float *pgUnk88;
      float *pgUnk8c;
      ACT *pactFirst;
      int xfk;
      short nRole;
      short nPhase;
      OID oid;
      XF *pxfParent;
      int nStampWorld;
      XF *pxfRef;
      short nUnkAc;
      short nUnkAe;
      VECTOR4 vUnkB0;
      qword qwRest;
      qword qwUnkD0;
      qword qwRestUnkE0;
      qword qwUnkF0;
};
qword ConvertXfPos(XF *pxfFrom, XF *pxfTo, qword qwPos) __asm__("func_0028E910");
struct SLOT
{
      SLOT *pslotNext;
};
struct SLOTHEAP
{
      int cb;
      int c;
      int cbAlign;
      SLOT *pslotFree;
      int cAlloc;
      byte *ab;
};
struct FILEREC
{
      uint aw[16];
};
struct TN;
struct GRABSPOTDATA
{
      TN *ptn;
      undefined4 unk_0x04;
      float sUnk08;
      undefined4 unk_0x0c;
      int nPriority;
      int nUnk14;
      int nGroup;
      uint grfUnk1c;
};
struct GRABSPOT : public GRABSPOTDATA
{
};
struct JTGRABCAND
{
      LO *plo;
      GRABSPOT *pspot;
      float sDist;
      int nPriority;
      LO *ploUnk10;
      float tUnk14;
      float sParam;
      float dsParam;
      qword qwPos;
};
struct SPLCS;
struct PO;
struct PROXYSRC;
struct CID116;
struct CID17;
struct REGTREE;
struct CELL
{
      qword plane;
      CELL *pcellNeg;
      CELL *pcellPos;
      int ileafNeg;
      int ileafPos;
};
struct LANGSTR
{
      int id;
      char *pchz;
};
struct SVN
{
      int nHash;
      char *pchzName;
      int id;
      SVN *psvnNext;
};
struct SVNHASH
{
      SVN *apsvn[0x35];
      int csvn;
      SVN *asvn;
};
struct SAVEVARS
{
      int crec;
      byte *arec;
      SVNHASH hash;
};
struct SVPATH
{
      int cid;
      short *aid;
};
struct LOUPD
{
      int grf;
      LO *plo;
};
struct HUDSTACK
{
      struct WIDGET *pwidget;
      float dyVel;
      int fSnap;
};
struct SW : public BASIC
{
      DL dlChild;
      LO *ploRemovedFirst;
      DL dlRoot;
      DL dlBusy;
      SL aslOid[512];
      SL aslPxrOid[512];
      SL aslCid[199];
      SLOTHEAP slotheapLoroot;
      LOROOT *plorootSettled;
      uint grfvisBusy;
      uint32_t   _pad_185    [ 1 ] ;
      VECTOR4 posCmBusy;
      VECTOR4 posHeroBusy;
      void *aUnk39d0;
      int cUnk39d4;
      void *aUnk39d8;
      int cUnk39dc;
      LO **aploNew;
      LO **pploNew;
      SPLCS *psplcs;
      SPLCS *psplcsHead;
      SL slEvent;
      SLOTHEAP slotheapEvent;
      int fUnk3a14;
      SAVEVARS savevars;
      int ctask;
      uint32_t   _pad_202    [ 3 ] ;
      LO *ploJobCur;
      LO *ploTaskCur;
      LO *ploTaskPending;
      LO *ploJobFailed;
      SVPATH *psvpDt;
      SVPATH *psvpCcoin;
      SVPATH *psvpWidCurrent;
      SVPATH *psvpEpisodeCurrent;
      SVPATH *psvpLang;
      SVPATH *psvpMixerMode;
      SVPATH *psvpMusicVolume;
      SVPATH *psvpEffectsVolume;
      SVPATH *psvpUseHeadset;
      SVPATH *psvpScreenCenterX;
      SVPATH *psvpScreenCenterY;
      SVPATH *psvpNoVibration;
      SVPATH *psvpReverseLookAround;
      SVPATH *psvpReverseAim;
      SVPATH *psvpAutosaveWarned;
      SVPATH *apsvpEpisodeDt[9];
      SVPATH *apsvpEpisodePercent[9];
      HUDSTACK ahudstack[4];
      uint32_t   _pad_228    [ 7 ] ;
      int fUnk3bec;
      int fUnk3bf0;
      uint grfUnk3bf4;
      FILEREC filerecDest;
      int nUnk3c38;
      int nUnk3c3c;
      uint32_t   _pad_235    [ 16 ] ;
      int nLoadFilter;
      int fUnk3c84;
      int nUnk3c88;
      int nUnk3c8c;
      SLOTHEAP slotheapCallback;
      SL slCallback;
      SLOTHEAP slotheapRefnode;
      int fAaoxUnsorted;
      int caaox;
      struct AAOX *aaaox[3];
      SLOTHEAP slotheapSotree;
      SLOTHEAP slotheapXplist;
      DL dlSoTreeAll;
      DL dlSoTree;
      DL dlSoTreeQueue1;
      DL dlSoTreeQueue2;
      SLOTHEAP slotheapXp;
      int nStampXf;
      int nUnk3d5c;
      int nStampLights;
      uint32_t   _pad_256    [ 1 ] ;
      int nStimulusSerial;
      int cEventWorld;
      int nUnk3d70;
      int nUnk3d74;
      int cHandsOff;
      int cNoPause;
      int cUnk3d80;
      int cUnk3d84;
      DL dlAsega;
      SLOTHEAP slotheapAsega;
      SLOTHEAP slotheapAct;
      SLOTHEAP slotheapOvra;
      DL dlSma;
      SLOTHEAP slotheapSma;
      RGBA rgbaClear;
      uint32_t   _pad_272    [ 3 ] ;
      VECTOR4 hsvLight;
      float gLightScale;
      float gMidtone;
      VECTOR vecLightRgb;
      float uMidtone;
      int fUnk3e38;
      uint32_t   _pad_279    [ 2 ] ;
      SLOTHEAP slotheapSobounds;
      void *pvUnk3e5c;
      CID116 *pcid116Fade;
      uint32_t   _pad_283    [ 18 ] ;
      SL slPoctl;
      uint cpo;
      PO *apo[16];
      PO *ppoHero;
      PO *ppoOverride;
      int cproxysrc;
      PROXYSRC *aproxysrc;
      PXR *ppxrRoot;
      int isrcLoading;
      int cloupd;
      int cloupdHole;
      int *piloupdCur;
      LOUPD *aloupd;
      DL dlTarget;
      DL dlCid11;
      DL dlCid13;
      DL dlCid39;
      DL dlCid88;
      DL dlCid12;
      DL dlCid34;
      DL dlCid38;
      DL dlCid35;
      DL dlCid40;
      DL dlCid9;
      DL dlCid27;
      DL dlStepguard;
      uint32_t   _pad_310    [ 6 ] ;
      DL dlCid47;
      uint32_t   _pad_312    [ 6 ] ;
      DL dlStimulus;
      SLOTHEAP slotheapStimulus;
      struct STIMK *apstimk[7];
      SLOTHEAP slotheapUnk403c;
      SLOTHEAP slotheapUnk4054;
      uint32_t   _pad_318    [ 1 ] ;
      SLOTHEAP slotheapUnk4070;
      SLOTHEAP slotheapUnk4088;
      uint32_t   _pad_321    [ 6 ] ;
      SLOTHEAP slotheapSsge;
      uint32_t   _pad_323    [ 6 ] ;
      SLOTHEAP slotheapXa;
      uint32_t   _pad_325    [ 6 ] ;
      SLOTHEAP slotheapZprHit;
      DL dlZprHit;
      uint32_t   _pad_328    [ 263 ] ;
      int ccell;
      CELL *acell;
      int cleaf;
      void *aleaf;
      uint32_t   _pad_333    [ 24 ] ;
      CID17 *pcid17Default;
      REGTREE *pregtree;
      CLQ clqGuardScale;
      LM lmGuardScale;
      uint32_t   _pad_338    [ 20 ] ;
      LO *ploUnk4638;
      int cCid37;
      int clangstr;
      LANGSTR *alangstr;
      uint32_t   _pad_343    [ 12 ] ;
      int cjtgrabcand;
      undefined4 unk_0x467c;
      JTGRABCAND ajtgrabcand[4];
      int idHintGrab;
      LO *ploUnk4744;
      int fGuardsFrozen;
      float tGuardsFrozen;
      float tLookLast;
      uint32_t   _pad_352    [ 2 ] ;
      float gUnk475c;
      uint32_t   _pad_354    [ 3 ] ;
      float tHudTimerEnd;
      int csecHudTimerShown;
      uint32_t   _pad_357    [ 1 ] ;
      int cpemitTracked;
      struct EMITTER *apemitTracked[4];
      uint32_t   _pad_360    [ 1 ] ;
};
struct SW3 { char pad[0x44F4]; int nStampXf; };
extern SW3 D_00475480;
#define g_sw D_00475480
struct CONSTR
{
      qword vecNormal;
      int nKind;
};
struct XA;
struct SOTREE;
struct SOPHYS
{
      MATRIX3 momintLocal;
      MATRIX3 momintInvLocal;
      qword qwVelocity;
      qword qwAngVelocity;
      VECTOR dvGravity;
      undefined4 unk_0x8c;
      CONSTR constrTorque;
      CONSTR constrForce;
      float m;
      undefined4 unk_0xd4[2];
      struct REGENT *pregent;
};
struct SO : public LO
{
      int cxf;
      XF *axf;
      XF *pxfUnk58;
      XF *pxfUnk5c;
      XF *pxfRoot;
      DL dlChild;
      LO *ploRemovedFirst;
      undefined4 unk_0x74[3];
      GLOBSET globset;
      int cpart;
      SOPART *apart;
      SOPHYS *psophys;
      SOTREE *ptree;
      qword qwDvContact;
      qword qwDwContact;
      uchar agrfZpk[26];
      undefined1 unk_0x12a[2];
      float uAlpha;
      float duAlpha;
      struct SOBOUNDS *psobounds;
      XA *pxa;
      float gUnk13c;
      int nStampUnk140;
      undefined4 unk_0x144;
      char bUnk148;
      char bUnk149;
      ulong unk_0x14a : 4;
                long nUnk14a : 4;
                ulong nZapMode : 2;
                ulong fIgnoreFixed : 1;
                ulong unk_0x14c : 2;
                ulong fNoJtPlace : 1;
                ulong unk_0x14d : 3;
                ulong fHurtRespawns : 1;
                ulong fTreeRoot : 1;
                ulong fUnk35 : 1;
                ulong fHasIkLimbs : 1;
};
struct CHAIN;
struct CHAINLINK
{
      MATRIX3 matRest;
      qword qwSeg;
      qword posTip;
      qword velTip;
      CHAIN *pchain;
      XF *pxf;
      int fDirty;
      undefined4 unk_0x6c;
};
struct CHAIN
{
      int clink;
      CHAINLINK *alink;
      int cstep;
      float gBend;
      float gDamp;
      float gDampRel;
      float radBendMax;
      float tLast;
      qword qwGravity;
      qword qwSegLast;
      qword posAnchorPrev;
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
static inline VU_FLOAT VuFloatFromMemWord(int n)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "rV"(n));
    return v;
}
static inline VU_FLOAT VuFloatFromClock(CLOCK *pclock)
{
    VU_FLOAT v;
    __asm__("qmtc2 %1, %0" : "=j"(v.qw) : "rV"(*(int *)&pclock->dt));
    return v;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwAdd(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
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
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwLengthUntied(qword v)
{
    qword qwSq;
    qword vfOne;
    qword qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qwSq), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qwSq));
    return qwLen;
}
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
qword func_0028BCD0(XF *pxfFrom, XF *pxfTo, qword qwPos) __asm__("func_0028BCD0");
float func_00120080(qword qwVec0, qword qwVec1, qword *pqwNormal) __asm__("func_00120080");
MATRIX3 LoadRotateMatrixRad(float rad, qword normal) __asm__("func_0011C8C0");
extern qword D_00317530;
static inline qword QwAddScaledA(qword qwBase, qword qwVec, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(gScale.qw));
    return qw;
}
static inline qword QwDivVf(qword qwVec, VU_FLOAT g)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qw) : "j"(g.qw), "j"(qwVec));
    return qw;
}
static inline qword QwScaleX(qword qwVec, qword qwScale)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwVec), "j"(qwScale));
    return qw;
}
static inline qword QwAddScaledX(qword qwBase, qword qwVec, qword qwScale)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(qwScale));
    return qw;
}
static inline qword QwChainVel(qword qwVel, VU_FLOAT gA, qword qwVelRel, VU_FLOAT gB, qword qwPerp, VU_FLOAT gK, qword qwGravity, VU_FLOAT gDt)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddax.xyzw $ACC, %3, %4x\n\tvmaddax.xyzw $ACC, %5, %6x\n\tvmaddx.xyzw %0, %7, %8x"
            : "=j"(qw) : "j"(qwVel), "j"(gA.qw), "j"(qwVelRel), "j"(gB.qw), "j"(qwPerp), "j"(gK.qw), "j"(qwGravity), "j"(gDt.qw), "j"(gDt.qw));
    return qw;
}
static inline float GMaxOf(float a, float b)
{
    return (a > b) ? a : b;
}
int UpdateChainLink(SO *pso, CHAINLINK *plink) __asm__("func_0026F190");
int UpdateChainLink(SO *pso, CHAINLINK *plink)
{
    CHAIN *pchain = plink->pchain;
    XF *pxf = plink->pxf;
    XF *pxfParent = pxf->pxfParent;
    VECTOR4 vecVel;
    int fMoved = 1;
    if (g_clock.t != pchain->tLast)
    {
        qword qwPos;
        qword qwDirPrev;
        int i;
        CHAINLINK *plinkCur;
        for (i = 0; i < pchain->clink; i++)
        {
            plinkCur = &pchain->alink[i];
            if (!(plinkCur < plink || plinkCur->fDirty || (*(uint *)pso->grfUnk40 & 0x10)))
                break;
            plinkCur->posTip = ConvertXfPos(plinkCur->pxf, 0, plinkCur->qwSeg);
            plinkCur->velTip = func_0028BCD0(plinkCur->pxf, 0, plinkCur->posTip);
            plinkCur->fDirty = 0;
        }
        if (plink == pchain->alink)
        {
            qword posAnchor = *(qword *)pxf->matWorld.mat[3];
            uint grf = *(uint *)pso->grfUnk40;
            qwPos = posAnchor;
            if (grf & 0x10)
            {
                *(qword *)&vecVel = func_0028BCD0(pxfParent, 0, posAnchor);
            }
            else
            {
                *(qword *)&vecVel = QwDivVf(QwSub(qwPos, pchain->posAnchorPrev), VuFloatFromClock(&g_clock));
            }
            pchain->posAnchorPrev = posAnchor;
            MATRIX3 matWorld3 = *(MATRIX3 *)&pxfParent->matWorld * plink->matRest;
            qwDirPrev = QwRotateVec(&matWorld3, plink->qwSeg);
        }
        else
        {
            *(qword *)&vecVel = plink[-1].velTip;
            qword *pqwPosPrev = &plink[-1].posTip;
            qwPos = *pqwPosPrev;
            if (plink - pchain->alink >= 2)
            {
                qword *pqwPosPrev2 = &plink[-2].posTip;
                qwDirPrev = QwSub(qwPos, *pqwPosPrev2);
            }
            else
            {
                qword *pqwSegPrev = &plink[-1].qwSeg;
                qwDirPrev = QwRotateVec((MATRIX3 *)&plink[-1].pxf->matWorld, *pqwSegPrev);
            }
        }
        float dtStep = g_clock.dt / pchain->cstep;
        fMoved = 0;
        int istep;
        for (istep = 0; istep < pchain->cstep; istep++)
        {
            int j = plink - pchain->alink;
            float tOff = (istep - pchain->cstep + 1) * dtStep;
            qword qwVelTip;
            qword posBase = QwAddScaledA(qwPos, *(qword *)&vecVel, VuFloat(tOff));
            qword velBase = *(qword *)&vecVel;
            qword qwDPrev = qwDirPrev;
            for (; j < pchain->clink; j++)
            {
                VECTOR4 vecDir;
                MATRIX3 mat;
                plinkCur = &pchain->alink[j];
                qword qwD;
                qwVelTip = plinkCur->velTip;
                qword qwVelRel = QwSub(qwVelTip, velBase);
                qword qwTip = plinkCur->posTip;
                qwD = QwSub(qwTip, posBase);
                float rad = func_00120080(qwD, qwDPrev, (qword *)&vecDir);
                if (pchain->radBendMax < rad)
                {
                    mat = LoadRotateMatrixRad(rad - pchain->radBendMax, *(qword *)&vecDir);
                    qwD = QwRotateVec(&mat, qwD);
                    qwTip = QwAdd(posBase, qwD);
                    rad = pchain->radBendMax;
                }
                qword qwDefault = D_00317530;
                float gA = GMaxOf(-pchain->gDamp * dtStep, -1.0f) + 1.0f;
                float gB = GMaxOf(-pchain->gDampRel * dtStep, -1.0f);
                float gK = pchain->gBend * rad * dtStep;
                VU_FLOAT vuA = VuFloat(gA);
                VU_FLOAT vuB = VuFloat(gB);
                VU_FLOAT vuK = VuFloat(gK);
                VU_FLOAT vuDt = VuFloat(dtStep);
                qword qwGravity = *(qword *)&pchain->qwGravity;
                qword qwPerp = *(qword *)&vecDir;
                qwPerp = QwCross(qwPerp, qwD);
                qword qwVelNew = QwChainVel(qwVelTip, vuA, qwVelRel, vuB, qwPerp, vuK, qwGravity, vuDt);
                qwTip = QwAddScaledA(qwTip, qwVelNew, vuDt);
                qword qwD2 = QwSub(qwTip, posBase);
                qword qwLen = QwLengthUntied(qwD2);
                qword qwV;
                if (GFromVf(qwLen) < 0.0001f)
                {
                    qwV = qwDefault;
                }
                else
                {
                    __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLen));
                    __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwV) : "j"(qwD2));
                }
                *(qword *)&vecDir = qwV;
                qword qwAlong = QwDot(qwVelNew, qwV);
                qword qwAlongBase = QwDot(velBase, qwV);
                qword qwVelOut = QwAdd(QwScaleX(qwV, qwAlongBase), QwSub(qwVelNew, QwScaleX(qwV, qwAlong)));
                qword qwSegLen = QwLength(plinkCur->qwSeg);
                qword qwTipOut = QwAddScaledX(posBase, qwV, qwSegLen);
                if (!fMoved && 0.01f < GFromVf(QwDot(QwSub(plinkCur->posTip, qwTipOut), QwSub(plinkCur->posTip, qwTipOut))))
                    fMoved = 1;
                plinkCur->posTip = qwTipOut;
                posBase = qwTipOut;
                plinkCur->velTip = qwVelOut;
                velBase = qwVelOut;
                qwDPrev = qwD;
            }
        }
        pchain->tLast = g_clock.t;
    }
    qword qwPosParent = ConvertXfPos(0, pxfParent, plink->posTip);
    qword qwTo = QwSub(qwPosParent, *(qword *)pxf->mat.mat[3]);
    qword qwFrom = QwRotateVec(&plink->matRest, plink->qwSeg);
    MATRIX3 matRot;
    matRot = BuildRotateVectorsMatrix(qwFrom, qwTo);
    *(MATRIX3 *)&pxf->mat = matRot * plink->matRest;
    pxf->mat.mat[1][3] = 0.0f;
    pxf->mat.mat[2][3] = 0.0f;
    pxf->mat.mat[0][3] = 0.0f;
    int nStamp = ++g_sw.nStampXf;
    pxf->nStampWorld = nStamp;
    return fMoved;
}
