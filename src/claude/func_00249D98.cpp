// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Reference: Sly 2 src/hand/func_001FFD98.cpp (RefGetPeopid / RefFromPv); target Sly 3 0x00249D98.
// The splice value of an option (EOPID record): a method, a member read directly, or a getter, by option type.
typedef unsigned char    uint8_t;
typedef unsigned int     uint32_t;
typedef uint8_t     uchar;
typedef uint32_t    uint;
typedef unsigned long long qword __attribute__((mode(TI)));
typedef uchar byte;
extern "C" void func_002BB798(void *, int);
template <class T>
class CGcObj
{
public:
      int m_cref;
      uint m_grfGc;
    void Release()
    {
        if (--m_cref == 0)
        {
            func_002BB798(this, 3);
        }
    }
};
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
struct BASIC;
class CRef;
class CMethod;
CMethod* PmethodNew() __asm__("func_002BF5B0");
enum BIFK
{
};
class CMethodPtr
{
public:
    CMethod *m_p;
    CMethodPtr() {}
    void Attach(CMethod *p) __asm__("func_002BF658");
    ~CMethodPtr();
    CMethod *operator->() { return m_p; }
    operator CMethod *() { return m_p; }
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
    CRef &operator=(int n);
    CRef &operator=(float g);
    CRef &operator=(bool f);
    CRef &operator=(void *pv);
    CRef &SetVector4(const VECTOR4 *pvec) __asm__("func_0012B400");
    CRef &SetVector4(qword qw) __asm__("__as__4CRefx");
    CRef &SetClq(CLQ *pclq) __asm__("func_0012B560");
    CRef &SetLm(LM *plm) __asm__("func_0012B5D0");
    CRef &SetSmp(SMP *psmp) __asm__("func_0012B648");
    CRef &SetMethod(CMethod *pmethod) __asm__("func_0012B7C8");
};
class CMethod : public CGcObj<CMethod>
{
public:
      CRef m_ref;
      CRef (*m_pfnthunk)(BASIC *, int, CRef *);
      int m_crefReq;
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
        long (BASIC::*pmfGetB)();
        float (BASIC::*pmfGetF)();
        qword (BASIC::*pmfGetQ)();
        MATRIX3 *(BASIC::*pmfGetM)();
        int (BASIC::*pmfGetN)();
        void (BASIC::*pmfGetClq)(CLQ *);
        void (BASIC::*pmfGetLm)(LM *);
        void (BASIC::*pmfGetSmp)(SMP *);
        CRef (BASIC::*pmfGetRef)();
        BASIC *(BASIC::*pmfGetPo)();
    };
      union
    {
        int ibSet;
        PMF pmfSet;
        PFNTHUNK pfnthunk;
    };
      union { SETTER setFile; int ibFile; int crefReq; };
      void *(BASIC::*pmfObj)(int);
};
struct PVREC : EOPID
{
};
inline CMethodPtr::~CMethodPtr()
{
    if (m_p)
    {
        m_p->Release();
    }
}
CRef RefFromPv(void *pv, PVREC *ppvrec) __asm__("func_00249D98");
CRef RefFromPv(void *pv, PVREC *ppvrec)
{
    CRef ref;
    uint grf = ppvrec->grfeopid;
    if (grf & 1)
    {
        CMethodPtr pmethod;
        CMethod *pmethodNew = PmethodNew();
        pmethod.Attach(pmethodNew);
        pmethod->m_ref = pv;
        pmethod->m_pfnthunk = ppvrec->pfnthunk;
        pmethod->m_crefReq = ppvrec->crefReq;
        ref.SetMethod(pmethod);
    }
    else if (grf & 2)
    {
        if (grf & 0x2000)
        {
            pv = (((BASIC *)pv)->*ppvrec->pmfObj)(0);
        }
        void *pf = (char *)pv + ppvrec->ib;
        switch (ppvrec->otyp)
        {
        case 5: case 6: case 7: case 8:
        case 14: case 15: case 16: case 17: case 19: case 20: case 23:
            ref = (*(int *)pf);
            break;
        case 1:
            ref = (*(float *)pf);
            break;
        case 0:
            ref = (bool)(*(int *)pf != 0);
            break;
        case 2:
            ref.SetVector4((VECTOR4 *)pf);
            break;
        case 4:
        {
            ref.Decref();
            ref.SetTag((TAGK)0x19);
            MATRIX4 *pmat = ref.m_tag.m_pmatrix;
            *(MATRIX3 *)pmat = *(MATRIX3 *)pf;
            pmat->mat[0][3] = 0.0f;
            pmat->mat[1][3] = 0.0f;
            pmat->mat[2][3] = 0.0f;
            break;
        }
        case 9:
            ref.SetClq((CLQ *)pf);
            break;
        case 10:
            ref.SetLm((LM *)pf);
            break;
        case 11:
            ref.SetSmp((SMP *)pf);
            break;
        case 13:
            break;
        default:
            if (ppvrec->otyp & 0x1000)
            {
                ref = (*(int *)pf);
            }
            else if (ppvrec->otyp & 0x2000)
            {
                ref = (void *)(*(BASIC **)pf);
            }
            break;
        }
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
            ref = ((pobj->*ppvrec->pmfGetN)());
            break;
        case 1:
            ref = ((pobj->*ppvrec->pmfGetF)());
            break;
        case 0:
            ref = (bool)((pobj->*ppvrec->pmfGetB)() != 0);
            break;
        case 2:
            ref.SetVector4((pobj->*ppvrec->pmfGetQ)());
            break;
        case 4:
        {
            ref.Decref();
            ref.SetTag((TAGK)0x19);
            MATRIX4 *pmat = ref.m_tag.m_pmatrix;
            MATRIX3 *pmatGot = (pobj->*ppvrec->pmfGetM)();
            *(MATRIX3 *)pmat = *pmatGot;
            pmat->mat[0][3] = 0.0f;
            pmat->mat[1][3] = 0.0f;
            pmat->mat[2][3] = 0.0f;
            break;
        }
        case 9:
            ref.Decref();
            ref.SetTag((TAGK)0x1a);
            (pobj->*ppvrec->pmfGetClq)(ref.m_tag.m_pclq);
            break;
        case 10:
            ref.Decref();
            ref.SetTag((TAGK)0x1a);
            (pobj->*ppvrec->pmfGetLm)(ref.m_tag.m_plm);
            break;
        case 11:
            ref.Decref();
            ref.SetTag((TAGK)0x1c);
            (pobj->*ppvrec->pmfGetSmp)(ref.m_tag.m_psmp);
            break;
        default:
            if (ppvrec->otyp & 0x8000)
            {
                CRef refGot = (pobj->*ppvrec->pmfGetRef)();
                ref = refGot;
            }
            else if (ppvrec->otyp & 0x1000)
            {
                ref = ((pobj->*ppvrec->pmfGetN)());
            }
            else if (ppvrec->otyp & 0x2000)
            {
                ref = (void *)((pobj->*ppvrec->pmfGetPo)());
            }
            break;
        }
    }
    return ref;
}
