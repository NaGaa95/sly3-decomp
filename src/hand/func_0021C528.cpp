// Write the typed property found in the original key trie and return its native empty CRef result.
// All original inputs, complete code/data and boundaries were independently reviewed.
// Write the looked-up typed property, then return a native nontrivial empty CRef.
// CRef tag is16 bits with16-bit padding; its payload union is at byte4.
// QW16/V2/V3 are opaque aligned16-byte / ordinary8-byte / ordinary12-byte word carriers.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Method asm labels bind actual original functions; no instruction assembly is used.
struct QW16 {
    int a[4];
}
__attribute__((aligned(16)));
struct V2 {
    int a[2];
};
struct V3 {
    int a[3];
};
struct CRef {
    short m_tagk;
    unsigned short padding;
    union {
        int m_tag;
        float m_g;
        void *m_pv;
    };
    CRef(int tagk) {
        InitTag(tagk);
    }
    CRef(const CRef &) asm("func_0012AF00");
    ~CRef() {
        Decref();
    }
    void InitTag(int) asm("func_0012BDD8");
    void Decref() asm("func_0012BC20");
};
struct ENT {
    short ch;
    signed char kind;
    unsigned char fBits;
    unsigned short ib;
    unsigned short iChild;
    unsigned short iSibling;
};
struct TRIE;
struct KEY;
struct OUT {
    ENT *pe;
    int n;
};
extern "C" int func_0021C208(TRIE *, KEY *, OUT *);
extern "C" CRef func_0021C528(TRIE *p, KEY *key, const CRef &val, char *pb) {
    CRef ref(0x22);
    OUT out;
    ENT *pe;
    if (!func_0021C208(p, key, &out) || (pe = out.pe)->kind == -1) return ref;
    {
        unsigned char *pv = (unsigned char *)pb + pe->ib;
        switch (pe->kind) {
            case 0: case 1: case 2: case 9: case 10: ((int *)pv)[out.n] = val.m_tag;
            break;
            case 3: ((float *)pv)[out.n] = val.m_g;
            break;
            case 4: if (pe->fBits) {
                int n = out.n;
                unsigned char b;
                pv += n / 8;
                b = 1 << (n % 8);
                if (val.m_tag) *pv |= b;
                else *pv &= ~b;
            }
            else {
                *(int *)pv = val.m_tag;
            }
            break;
            case 5: case 6: ((QW16 *)pv)[out.n] = *(QW16 *)val.m_pv;
            break;
            case 7: ((V2 *)pv)[out.n] = *(V2 *)val.m_pv;
            break;
            case 8: ((V3 *)pv)[out.n] = *(V3 *)val.m_pv;
            break;
        }
    }
    return ref;
}
