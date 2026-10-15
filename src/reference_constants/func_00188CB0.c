// Reference algorithm: src/hand/func_00164270.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct Y;
struct X { char pad[0x44]; int n; char pad1[0x64 - 0x58]; struct X *f64; char pad2[0x7C - 0x68]; struct Owner *f7c; char pad3[0x94 - 0x80]; int c; struct X **apx; char pad4[0xE8 - 0x8C]; int fe0; int pad5; int fe8; };
struct Owner { char pad[0x54]; struct X *f64; char pad2[0x7C - 0x58]; struct Owner *f7c; };
extern char D_00468D30[];
void func_002BC010(CRef *pref, void *a, void *b);
void func_0012BC20(CRef *pref);
void func_0018A3E8(struct X *p, int n);
void func_00188CB0(struct X *p)
{
    CRef ref;
    int *pn;
    int n = 0;
    int f;
    pn = &p->fe0;
    f = 0;
    if (*pn) {
        int nT;
        func_002BC010(&ref, pn, D_00468D30);
        nT = ref.m_tag;
        func_0012BC20(&ref);
        n = nT;
    }
    pn = &p->fe8;
    if (*pn) {
        int nT;
        func_002BC010(&ref, pn, D_00468D30);
        nT = ref.m_tag;
        func_0012BC20(&ref);
        f = nT;
    }
    if (f && p->f7c && n < 3 && n > 0) {
        struct Owner *pxOwner = p->f7c;
        int i;
        p->f64 = 0;
        n = 1;
        if (pxOwner->f64 == p)
            pxOwner->f7c = 0;
        for (i = 0; i < p->c; i++) {
            if (p->apx[i]->n < 2) {
                n = 0;
                break;
            }
        }
    }
    if (!n)
        n = p->c == 0;
    func_0018A3E8(p, n);
}
