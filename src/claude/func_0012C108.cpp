// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Script value loader (Sly 2 func_0012A3D8 evolved): reads a tag byte, builds a NODE holding the value, recursing for
// lists (tag 29) and for the next node (bit 7). Sly 3 tags are mostly 2 lower and CRef has a short tag + short refcount.
struct NODE; struct OBJ; struct T18; struct T19; struct BIS;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; float *ag; NODE *pnode; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(int n);
    CRef &operator=(float g);
    CRef &operator=(bool f);
    CRef &operator=(void *p);
    CRef &operator=(T18 *p) __asm__("func_0012B330");
    CRef &operator=(T19 *p) __asm__("func_0012B370");
    CRef &operator=(NODE *p) __asm__("func_0012B6C8");
    void SetTag(int tagk) { Decref(); InitTag(tagk); }
};
extern int D_0047A488;
extern "C" {
NODE *func_002BA6B8();
void func_002BA840(NODE *, int);
int func_00118FF8(BIS *pbis);
int func_001191E0(BIS *pbis);
int func_00119178(BIS *pbis);
float func_00119260(BIS *pbis);
unsigned int func_001190A8(BIS *pbis);
}
struct SPM {
    NODE *p;
    void operator=(NODE *pn) __asm__("func_002BA780");
};
struct NODE {
    CRef ref;
    int x8;
    SPM pnext;
};
struct SPN {
    NODE *p;
    void Set(NODE *pn) __asm__("func_002BA760");
    SPN() {}
    SPN(NODE *pn) { Set(pn); }
    SPN(const SPN &);
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    NODE *operator->() { return p; }
};
extern "C" SPN func_0012C108(BIS *pbis);
extern "C" SPN func_0012C108(BIS *pbis)
{
    unsigned int b = func_00118FF8(pbis);
    if (b == 0xFF)
        return SPN(0);
    SPN sp;
    NODE *pnNew = func_002BA6B8();
    sp.Set(pnNew);
    if (D_0047A488) {
        func_001191E0(pbis);
        func_00119178(pbis);
        func_00119178(pbis);
        func_00119178(pbis);
        func_00119178(pbis);
        func_00119178(pbis);
        func_00119178(pbis);
    }
    CRef *pref = &sp->ref;
    int fNext = (b >> 7) & 0xFF;
    int tagk = b & 0x7F;
    switch (tagk) {
    case 0: case 1: case 2: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
    case 15: case 16: case 18:
        pref->SetTag(tagk);
        break;
    case 19: *pref = func_001191E0(pbis); break;
    case 20: *pref = func_00119260(pbis); break;
    case 21: *pref = func_001190A8(pbis) != 0; break;
    case 31: *pref = (void *)func_001190A8(pbis); break;
    case 22: *pref = (T18 *)func_001190A8(pbis); break;
    case 23: *pref = (T19 *)func_001190A8(pbis); break;
    case 24: pref->SetTag(0x18); for (int i = 0; i < 3; i++) { float *pg = &pref->u.ag[i]; *pg = func_00119260(pbis); } break;
    case 25: pref->SetTag(0x19); for (int i = 0; i < 16; i++) { float *ag = pref->u.ag; float g = func_00119260(pbis); ag += i; *ag = g; } break;
    case 26: pref->SetTag(0x1A); for (int i = 0; i < 3; i++) { float *ag = pref->u.ag; float g = func_00119260(pbis); ag += i; *ag = g; } break;
    case 27: pref->SetTag(0x1B); for (int i = 0; i < 2; i++) { float *ag = pref->u.ag; float g = func_00119260(pbis); ag += i; *ag = g; } break;
    case 28: pref->SetTag(0x1C); for (int i = 0; i < 3; i++) { float *ag = pref->u.ag; float g = func_00119260(pbis); ag += i; *ag = g; } break;
    case 29: *pref = func_0012C108(pbis).p; break;
    }
    if (fNext) {
        NODE *pn = sp.p;
        SPN next = func_0012C108(pbis);
        pn->pnext = next.p;
    }
    return SPN(sp.p);
}
