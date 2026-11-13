// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// LoadOptionFromBrx port (Sly 2 0.876): the method-option arguments are read straight into CRef slots (func_0012BC20
// Decref, func_0012BDD8 SetTag, func_0012B3B0 assign); list arguments build a CPair chain held by a PAIRPTR whose
// short refcount is released at scope exit. Reading *pp into its own local before RefFromBrx gives the target its
// extra s-register, which is what leaves grfeopid in its stack slot. Started by A108, finished by A111.
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long qword __attribute__((mode(TI)));
struct LO;
struct BASIC;
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct SMP { float svFast, svSlow, dtFast; };
struct SMPA { float svFast, svSlow, dtFast, sdvMax; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct RGBA { uchar r, g, b, a; };
struct LORUN { void (*pfn)(LO *, void *); void *pv; };
struct CBinaryInputStream;
struct CPair;
class CRef {
public:
    short m_tagk;
    short m_pad;
    int m_tag;
    CRef() { m_tagk = -1; }
    ~CRef() { Decref(); }
    void Decref() __asm__("func_0012BC20");
    void SetTag(int tagk) __asm__("func_0012BDD8");
    CRef &operator=(const CRef &ref) __asm__("func_0012B3B0");
    CRef &operator=(CPair *ppair) __asm__("func_0012B6C8");
};
struct CPair { CRef ref; int x8; CPair *pnext; };
struct SCOPE { int a[4]; };
struct ARR { int c; void *pv; };
typedef void (BASIC::*PMF)();
typedef CRef (*PFNTHUNK)(BASIC *, int, CRef *);
union SETTER { int ibSet; PMF pmfSet; PFNTHUNK pfnthunk; void (BASIC::*pmfSetN)(int); };
struct EOPID {
    int otyp;
    int grfeopid;
    union { int ib; PFNTHUNK pfnthunkDeferred; PMF pmfGet; };
    union { int ibSet; PMF pmfSet; PFNTHUNK pfnthunk; void (BASIC::*pmfSetN)(int); };
    union { SETTER setFile; int ibFile; int crefReq; };
    void *(BASIC::*pmfObj)(int);
};
struct OIDFIELD { int oid; int ib; };
struct OIDSETTER { int oid; SETTER setter; };
extern char D_00475480[];
extern char D_0036B118[];
extern "C" {
uchar func_00118FF8(CBinaryInputStream *);
ushort func_00119048(CBinaryInputStream *);
short func_00119178(CBinaryInputStream *);
int func_001191E0(CBinaryInputStream *);
uint func_001190A8(CBinaryInputStream *);
float func_00119260(CBinaryInputStream *);
void func_00119968(CBinaryInputStream *, void *, void *);
CPair *func_002BA6B8(void);
void func_002BA780(CPair **, CPair *);
void func_002BA840(CPair *, int);
CRef *func_00150960(CRef *, int, CBinaryInputStream *);
void func_00236908(RGBA *);
MATRIX3 func_0011C930(qword);
void *func_0025D5C8(void *);
LORUN *func_001C7ED8(LO *);
void func_00150860(LO *, void *);
void func_001508B0(LO *, void *);
void func_002BC528(SCOPE *);
void func_002BC4D8(SCOPE *, int);
}
CRef RefFromBrx(int otyp, CBinaryInputStream *pbis) __asm__("func_00150960");
struct PAIRPTR {
    CPair *p; char ab[0];
    ~PAIRPTR() { CPair *ppair = p; if (ppair && --((short *)ppair)[1] == 0) func_002BA840(ppair, 3); }
};
extern "C" void func_00150AE8(void *const pvStruct, EOPID *peopid, int grfeopid, CBinaryInputStream *pbis)
{
    if (grfeopid & 0x401)
    {
        CRef aref[32];
        int carg = peopid->crefReq;
        for (int iarg = 0; iarg < carg; iarg++)
        {
            int otyp = func_00119048(pbis);
            if (otyp & 0x8000)
            {
                int cElt = func_00118FF8(pbis);
                if (cElt == 0)
                {
                    aref[iarg].Decref();
                    aref[iarg].SetTag(0);
                }
                else
                {
                    PAIRPTR list;
                    list.p = 0;
                    otyp &= ~0x8000;
                    CPair **pp = &list.p;
                    while (cElt-- != 0)
                    {
                        func_002BA780(pp, func_002BA6B8());
                        CPair *ppair = *pp;
                        ppair->ref = RefFromBrx(otyp, pbis);
                        pp = &(*pp)->pnext;
                    }
                    aref[iarg] = list.p;
                }
            }
            else
            {
                aref[iarg] = RefFromBrx(otyp, pbis);
            }
        }
        if (grfeopid & 0x400)
        {
            CRef ref = (*peopid->pfnthunkDeferred)((BASIC *)pvStruct, carg, aref);
        }
        else
        {
            CRef ref = (*peopid->pfnthunk)((BASIC *)pvStruct, carg, aref);
        }
        return;
    }
    if (grfeopid & 0x90)
    {
        char *pf;
        if (grfeopid & 0x2000)
        {
            void *(BASIC::*pmfObj)(int) = peopid->pmfObj;
            pf = (char *)(((BASIC *)pvStruct)->*pmfObj)(1) + peopid->ibFile;
        }
        else
        {
            pf = (char *)pvStruct + peopid->ibFile;
        }
        switch (peopid->otyp)
        {
        case 0:
            *(uchar *)pf = func_00118FF8(pbis);
            return;
        case 5:
        case 6:
            *(int *)pf = func_001191E0(pbis);
            return;
        case 1:
            *(float *)pf = func_00119260(pbis);
            return;
        case 10:
            ((float *)pf)[0] = func_00119260(pbis);
            ((float *)pf)[1] = func_00119260(pbis);
            return;
        case 2:
        case 9:
        case 11:
            ((float *)pf)[0] = func_00119260(pbis);
            ((float *)pf)[1] = func_00119260(pbis);
            ((float *)pf)[2] = func_00119260(pbis);
            return;
        case 3:
        case 12:
            ((float *)pf)[0] = func_00119260(pbis);
            ((float *)pf)[1] = func_00119260(pbis);
            ((float *)pf)[2] = func_00119260(pbis);
            ((float *)pf)[3] = func_00119260(pbis);
            return;
        case 13:
        {
            RGBA rgba;
            *(uint *)&rgba = func_001190A8(pbis);
            func_00236908(&rgba);
            *(uint *)pf = *(uint *)&rgba;
            return;
        }
        case 4:
        {
            VECTOR4 vec;
            vec.x = func_00119260(pbis);
            vec.y = func_00119260(pbis);
            vec.z = func_00119260(pbis);
            *(MATRIX3 *)pf = func_0011C930(*(qword *)&vec);
            return;
        }
        case 22:
            func_00119968(pbis, pf, D_0036B118);
            return;
        case 7:
        case 14:
        case 15:
        case 16:
        case 17:
        case 19:
        case 20:
        case 21:
        case 23:
            *(int *)pf = func_00119178(pbis);
            return;
        default:
            switch ((peopid->otyp & ~0x8000) >> 12)
            {
            case 1:
                *(uint *)pf = func_001190A8(pbis);
                return;
            case 2:
                if (grfeopid & 0x80)
                {
                    int oid = func_001191E0(pbis);
                    OIDFIELD *poidfield = (OIDFIELD *)func_0025D5C8(D_00475480);
                    poidfield->oid = oid;
                    poidfield->ib = pf - (char *)pvStruct;
                    LORUN *plorun = func_001C7ED8((LO *)pvStruct);
                    plorun->pv = poidfield;
                    plorun->pfn = func_00150860;
                    return;
                }
                OIDFIELD oidfield;
                oidfield.oid = func_001191E0(pbis);
                oidfield.ib = peopid->ibSet;
                func_00150860((LO *)pvStruct, &oidfield);
                return;
            }
            return;
        }
    }
    BASIC *pbasic;
    if (grfeopid & 0x2000)
    {
        void *(BASIC::*pmfObj)(int) = peopid->pmfObj;
        pbasic = (BASIC *)(((BASIC *)pvStruct)->*pmfObj)(1);
    }
    else
    {
        pbasic = (BASIC *)pvStruct;
    }
    void (BASIC::*pmfSet)(int);
    if (grfeopid & 0x100)
    {
        pmfSet = peopid->setFile.pmfSetN;
    }
    else
    {
        pmfSet = peopid->pmfSetN;
    }
    switch (peopid->otyp)
    {
    case 0:
        (pbasic->*pmfSet)(func_00118FF8(pbis));
        break;
    case 5:
    case 6:
        (pbasic->*pmfSet)(func_001191E0(pbis));
        break;
    case 1:
        (pbasic->*(void (BASIC::*)(float))pmfSet)(func_00119260(pbis));
        break;
    case 10:
    {
        LM lm;
        lm.gMin = func_00119260(pbis);
        lm.gMax = func_00119260(pbis);
        (pbasic->*(void (BASIC::*)(LM *))pmfSet)(&lm);
        break;
    }
    case 9:
    {
        CLQ clq;
        float g0 = func_00119260(pbis);
        float g1 = func_00119260(pbis);
        float g2 = func_00119260(pbis);
        clq.g0 = g0;
        clq.g1 = g1;
        clq.g2 = g2;
        (pbasic->*(void (BASIC::*)(CLQ *))pmfSet)(&clq);
        break;
    }
    case 11:
    {
        SMP smp;
        float g0 = func_00119260(pbis);
        float g1 = func_00119260(pbis);
        float g2 = func_00119260(pbis);
        smp.svFast = g0;
        smp.svSlow = g1;
        smp.dtFast = g2;
        (pbasic->*(void (BASIC::*)(SMP *))pmfSet)(&smp);
        break;
    }
    case 2:
    {
        float gX = func_00119260(pbis);
        float gY = func_00119260(pbis);
        float gZ = func_00119260(pbis);
        qword q;
        int iTmp;
        __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
                : "=&r"(q), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
        VECTOR4 vec;
        *(qword *)&vec = q;
        (pbasic->*(void (BASIC::*)(qword))pmfSet)(q);
        break;
    }
    case 12:
    {
        SMPA smpa;
        float g0 = func_00119260(pbis);
        float g1 = func_00119260(pbis);
        float g2 = func_00119260(pbis);
        float g3 = func_00119260(pbis);
        smpa.svFast = g0;
        smpa.svSlow = g1;
        smpa.dtFast = g2;
        smpa.sdvMax = g3;
        (pbasic->*(void (BASIC::*)(SMPA *))pmfSet)(&smpa);
        break;
    }
    case 3:
    {
        float gX = func_00119260(pbis);
        float gY = func_00119260(pbis);
        float gZ = func_00119260(pbis);
        float gW = func_00119260(pbis);
        qword q; qword qwZW; qword qwTmp;
        __asm__("mfc1 %0, %3\n\tmfc1 %1, %4\n\tpextlw %0, %1, %0\n\tmfc1 %1, %5\n\tmfc1 %2, %6\n\tpextlw %1, %2, %1\n\tpcpyld %0, %1, %0"
                : "=&r"(q), "=&r"(qwZW), "=&r"(qwTmp) : "f"(gX), "f"(gY), "f"(gZ), "f"(gW));
        VECTOR4 vec;
        *(qword *)&vec = q;
        (pbasic->*(void (BASIC::*)(qword))pmfSet)(q);
        break;
    }
    case 13:
    {
        RGBA rgba;
        *(uint *)&rgba = func_001190A8(pbis);
        func_00236908(&rgba);
        RGBA rgbaSet = rgba;
        (pbasic->*(void (BASIC::*)(RGBA *))pmfSet)(&rgbaSet);
        break;
    }
    case 4:
    {
        VECTOR4 vec;
        vec.x = func_00119260(pbis);
        vec.y = func_00119260(pbis);
        vec.z = func_00119260(pbis);
        MATRIX3 mat;
        mat = func_0011C930(*(qword *)&vec);
        (pbasic->*(void (BASIC::*)(MATRIX3 *))pmfSet)(&mat);
        break;
    }
    case 22:
    {
        SCOPE scope;
        func_002BC528(&scope);
        ARR arr;
        func_00119968(pbis, &arr, &scope);
        (pbasic->*(void (BASIC::*)(void *))pmfSet)(&arr);
        func_002BC4D8(&scope, 2);
        break;
    }
    case 7:
    case 14:
    case 15:
    case 16:
    case 17:
    case 19:
    case 20:
    case 21:
    case 23:
        (pbasic->*pmfSet)(func_00119178(pbis));
        break;
    default:
        switch ((peopid->otyp & ~0x8000) >> 12)
        {
        case 1:
            (pbasic->*pmfSet)(func_001190A8(pbis));
            break;
        case 2:
            if (grfeopid & 0x100)
            {
                int oid = func_001191E0(pbis);
                OIDSETTER *poidsetter = (OIDSETTER *)func_0025D5C8(D_00475480);
                poidsetter->oid = oid;
                poidsetter->setter = peopid->setFile;
                LORUN *plorun = func_001C7ED8((LO *)pvStruct);
                plorun->pv = poidsetter;
                plorun->pfn = func_001508B0;
                return;
            }
            OIDSETTER oidsetter;
            oidsetter.oid = func_001191E0(pbis);
            oidsetter.setter = *(SETTER *)&peopid->pmfSet;
            func_001508B0((LO *)pvStruct, &oidsetter);
            break;
        }
        break;
    }
}
