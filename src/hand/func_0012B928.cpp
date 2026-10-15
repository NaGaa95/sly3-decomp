// Clone tagged payloads, recursively copying node/object carriers and retaining the resulting value.
// CRef is 8 bytes: tag16/padding16/payload32. NODE and O declare only their consumed prefixes.
// Method asm names bind original constructors; no instruction assembly is used.
// Hidden CRef output A0, source A1 and both recursive contexts A2/A3 are expressed by the native ABI.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Actual 16-bit tag and counter; RAII cleanup supplies the real destructor flags explicitly.
struct VECTOR;
struct MATRIX4;
struct V16;
struct V8;
struct V12;
struct OBJ;
struct NODE;
struct O;
extern "C" {
}
struct CRef {
    short m_tagk;
    unsigned short padding;
    union {
        int n;
        float g;
        void *pv;
    }
    u;
    CRef() {
        m_tagk = -1;
    }
    CRef(const CRef &r) asm("func_0012AF00");
    CRef(const VECTOR *pv) asm("func_0012AF38");
    CRef(const MATRIX4 *pm) asm("func_0012B008");
    CRef(const V16 *p) asm("func_0012B088");
    CRef(const V8 *p) asm("func_0012B0F0");
    CRef(const V12 *p) asm("func_0012B160");
    CRef(NODE *p) asm("func_0012B1D8");
    CRef(O *p) asm("func_0012B1F8");
    CRef(OBJ *p) asm("func_0012B218");
    void Decref() asm("func_0012BC20");
    ~CRef() {
        Decref();
    }
};
struct NODE {
    short tag0;
    short cref;
};
extern "C" void func_002BA840(NODE *, int);
extern "C" void func_002BAC20(O *, int);
struct SPN {
    NODE *p;
    SPN(const SPN &);
    ~SPN() {
        NODE *pn = p;
        if (pn && --pn->cref == 0) func_002BA840(pn, 3);
    }
};
struct O {
    int cref;
};
struct SPO {
    O *p;
    SPO(const SPO &);
    ~SPO() {
        O *po = p;
        if (po && --po->cref == 0) func_002BAC20(po, 3);
    }
};
extern "C" {
    SPN func_0012AA50(NODE *pn, void *a, void *b);
    SPO func_0012ACC8(O *po, void *a);
    CRef func_0012B928(CRef *pref, void *a, void *b);
}
CRef func_0012B928(CRef *pref, void *a, void *b) {
    switch (pref->m_tagk) {
        case 0x18: return CRef((const VECTOR *)pref->u.pv);
        case 0x19: return CRef((const MATRIX4 *)pref->u.pv);
        case 0x1A: return CRef((const V16 *)pref->u.pv);
        case 0x1B: return CRef((const V8 *)pref->u.pv);
        case 0x1C: return CRef((const V12 *)pref->u.pv);
        case 0x1D: return CRef(func_0012AA50((NODE *)pref->u.pv, a, b).p);
        case 0x1E: return CRef(func_0012ACC8((O *)pref->u.pv, a).p);
        case 0x1F: return CRef((OBJ *)pref->u.pv);
    }
    return CRef(*pref);
}
