// Read a typed key property into the actual native CRef result, preserving raw Boolean words.
// Complete original inputs, code/table and actual boundary independently reviewed.
// Read the typed property into a native nontrivial CRef return object.
// Tag is signed16 bits, padding is16 bits, and the payload word is at byte4.
// A default invalid tag leaves its payload untouched, as in the original constructor.
// Unpacked Boolean payloads retain all32 bits; only packed-bit tests normalize0/1.
// VECTOR/QW16/V2/V3 preserve complete16/16/8/12-byte carriers.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 tag15 setter preserves its actual32-bit Boolean payload; packed bits are normalized separately.
// Method asm labels bind actual original functions; no instruction assembly is used.
struct VECTOR {
    float x, y, z;
}
__attribute__((aligned(16)));
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
    int m_tag;
    CRef() {
        m_tagk = -1;
    }
    CRef(const CRef &) asm("func_0012AF00");
    ~CRef() {
        Decref();
    }
    CRef &operator=(int) asm("func_0012B270");
    CRef &operator=(float) asm("func_0012B2B0");
    CRef &SetBooleanWord(int) asm("func_0012B2F0");
    CRef &operator=(const VECTOR &) asm("func_0012B400");
    CRef &operator=(const QW16 &) asm("func_0012B560");
    CRef &operator=(const V2 &) asm("func_0012B5D0");
    CRef &operator=(const V3 &) asm("func_0012B648");
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
extern "C" CRef func_0021C338(TRIE *p, KEY *key, unsigned char *pb) {
    CRef ref;
    OUT out;
    ENT *pe;
    if (!func_0021C208(p, key, &out) || (pe = out.pe)->kind == -1) return ref;
    {
        unsigned char *pv = (unsigned char *)pb + pe->ib;
        switch (pe->kind) {
            case 0: case 1: case 2: case 10: ref = ((int *)pv)[out.n];
            break;
            case 3: ref = ((float *)pv)[out.n];
            break;
            case 4: if (pe->fBits) {
                int n = out.n;
                unsigned char b;
                pv += n / 8;
                b = 1 << (n % 8);
                ref.SetBooleanWord((*pv & b) != 0);
            }
            else {
                ref.SetBooleanWord(*(int *)pv);
            }
            break;
            case 5: ref = ((VECTOR *)pv)[out.n];
            break;
            case 6: ref = ((QW16 *)pv)[out.n];
            break;
            case 7: ref = ((V2 *)pv)[out.n];
            break;
            case 8: ref = ((V3 *)pv)[out.n];
            break;
            case 9: ref = ((int *)pv)[out.n];
            break;
        }
    }
    return ref;
}
