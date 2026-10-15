// Reference algorithm: src/hand/InitTag__4CRef.c; canonical Sly 3 identity.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct CRef { short m_tagk; short unknown_tag_padding; void *m_pv; } CRef;
typedef struct SLOTHEAP { int a[6]; } SLOTHEAP;
typedef struct NV { qword v; int cref; } NV;
typedef struct NM { qword m[4]; int cref; } NM;
typedef struct N2 { int a[2]; int cref; } N2;
typedef struct N3 { int a[3]; int cref; } N3;
extern SLOTHEAP D_004D2F28;
extern SLOTHEAP D_004D2F40;
extern SLOTHEAP D_004D2F58;
extern SLOTHEAP D_004D2F70;
extern SLOTHEAP D_004D2F88;
void *func_0011E118(SLOTHEAP *psh);
void func_0012BDD8(CRef *pref, int tagk)
{
    pref->m_tagk = tagk;
    switch (pref->m_tagk) {
    case 0x18: {
        NV *p = (NV *)func_0011E118(&D_004D2F28);
        p->cref = 0;
        pref->m_pv = p;
        p->cref++;
        break;
    }
    case 0x19: {
        NM *p = (NM *)func_0011E118(&D_004D2F40);
        p->cref = 0;
        pref->m_pv = p;
        p->cref++;
        break;
    }
    case 0x1A: {
        NV *p = (NV *)func_0011E118(&D_004D2F58);
        p->cref = 0;
        pref->m_pv = p;
        p->cref++;
        break;
    }
    case 0x1B: {
        N2 *p = (N2 *)func_0011E118(&D_004D2F70);
        p->cref = 0;
        pref->m_pv = p;
        p->cref++;
        break;
    }
    case 0x1C: {
        N3 *p = (N3 *)func_0011E118(&D_004D2F88);
        p->cref = 0;
        pref->m_pv = p;
        p->cref++;
        break;
    }
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    default:
        pref->m_pv = 0;
        break;
    }
}
