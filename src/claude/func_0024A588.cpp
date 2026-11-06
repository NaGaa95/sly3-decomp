// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_00200598.cpp (RefSetPeopid); target Sly 3 0x0024A588.
// The setter twin of RefGetPeopid (func_00249D98): writes *pref into option *ppvrec of the object pv; returns the void reference.
typedef unsigned char    uint8_t;
typedef unsigned int     uint32_t;
typedef uint8_t     uchar;
typedef uint32_t    uint;
typedef unsigned long long qword __attribute__((mode(TI)));
typedef uchar byte;
struct BASIC;
class CRef;
class CMethod;
enum BIFK
{
};
struct CLQ;
struct LM;
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
struct SMP;
class CPair;
class CProc;
enum TAGK
{
    TAGK_Nil = -1,
};
union TAG
{
    int m_n;
    float m_g;
    int m_bool;
    uint m_symid;
    BIFK m_bifk;
    const VECTOR4* m_pvec4;
    CPair* m_ppair;
    CProc* m_pproc;
    VECTOR* m_pvector;
    MATRIX4* m_pmatrix;
    CLQ* m_pclq;
    LM* m_plm;
    SMP* m_psmp;
    BASIC* m_pbasic;
    CMethod* m_pmethod;
};
class CRef
{
public:
    short m_tagk;
    TAG m_tag;
    CRef() { m_tagk = TAGK_Nil; }
    CRef(const CRef &ref) __asm__("func_0012AF00");
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &ref);
    void Decref();
    void SetTag(TAGK tagk) __asm__("InitTag__4CRefi");
    CRef RefCoerceS32() const __asm__("func_0012BA98");
    CRef RefCoerceF32() const __asm__("func_0012BAE8");
};
typedef int GRFEOPID;
enum OTYP
{
};
typedef void (BASIC::*PMF)();
typedef CRef (*PFNTHUNK)(BASIC *, int, CRef *);
union SETTER
{
    int ibSet;
    PMF pmfSet;
    PFNTHUNK pfnthunk;
};
struct EOPID
{
      OTYP otyp;
      GRFEOPID grfeopid;
      union
    {
        int ib;
        PFNTHUNK pfnthunkDeferred;
        PMF pmfGet;
    };
      union
    {
        int ibSet;
        PMF pmfSet;
        PFNTHUNK pfnthunk;
        void (BASIC::*pmfSetB)(int);
        void (BASIC::*pmfSetF)(float);
        void (BASIC::*pmfSetQ)(qword);
        void (BASIC::*pmfSetN)(int);
        void (BASIC::*pmfSetM)(MATRIX3 *);
        void (BASIC::*pmfSetClq)(CLQ *);
        void (BASIC::*pmfSetLm)(LM *);
        void (BASIC::*pmfSetSmp)(SMP *);
        void (BASIC::*pmfSetPo)(BASIC *);
    };
      union { SETTER setFile; int ibFile; int crefReq; };
      void *(BASIC::*pmfObj)(int);
};
CRef RefSetPvsFromSplice(int cref, CRef *aref, OTYP *aotyp, void **apv) __asm__("func_0024B068");
struct PVREC : EOPID
{
};
CRef RefSetPeopid(void *pv, PVREC *ppvrec, CRef *pref) __asm__("func_0024A588");
CRef RefSetPeopid(void *pv, PVREC *ppvrec, CRef *pref)
{
    CRef ref;
    ref.Decref();
    ref.SetTag((TAGK)0x22);
    uint grf = ppvrec->grfeopid;
    if (grf & 0x10)
    {
        if (grf & 0x2000)
        {
            pv = (((BASIC *)pv)->*ppvrec->pmfObj)(1);
        }
        void *pvTarget = (char *)pv + ppvrec->ibSet;
        ref = RefSetPvsFromSplice(1, pref, (OTYP *)ppvrec, &pvTarget);
    }
    else
    {
        if (grf & 0x2000)
        {
            pv = (((BASIC *)pv)->*ppvrec->pmfObj)(1);
        }
        BASIC *pobj = (BASIC *)pv;
        switch (ppvrec->otyp)
        {
        case 5: case 6: case 7: case 8: case 13:
        case 14: case 15: case 16: case 17: case 19: case 20: case 23:
        {
            int n;
            if (pref->m_tagk == 0x13)
            {
                n = pref->m_tag.m_n;
            }
            else
            {
                CRef refInt;
                refInt = pref->RefCoerceS32();
                n = refInt.m_tag.m_n;
            }
            (pobj->*ppvrec->pmfSetN)(n);
            break;
        }
        case 1:
        {
            float g;
            if (pref->m_tagk == 0x14)
            {
                g = pref->m_tag.m_g;
            }
            else
            {
                CRef refF;
                refF = pref->RefCoerceF32();
                g = refF.m_tag.m_g;
            }
            (pobj->*ppvrec->pmfSetF)(g);
            break;
        }
        case 0:
            (pobj->*ppvrec->pmfSetB)(pref->m_tag.m_bool);
            break;
        case 2:
            (pobj->*ppvrec->pmfSetQ)(*(qword *)pref->m_tag.m_pvector);
            break;
        case 4:
            (pobj->*ppvrec->pmfSetM)((MATRIX3 *)pref->m_tag.m_pmatrix);
            break;
        case 9:
            (pobj->*ppvrec->pmfSetClq)(pref->m_tag.m_pclq);
            break;
        case 10:
            (pobj->*ppvrec->pmfSetLm)(pref->m_tag.m_plm);
            break;
        case 11:
            (pobj->*ppvrec->pmfSetSmp)(pref->m_tag.m_psmp);
            break;
        default:
            if (ppvrec->otyp & 0x1000)
            {
                (pobj->*ppvrec->pmfSetN)(pref->m_tag.m_n);
            }
            else if (ppvrec->otyp & 0x2000)
            {
                (pobj->*ppvrec->pmfSetPo)(pref->m_tag.m_pbasic);
            }
            break;
        }
    }
    return ref;
}
