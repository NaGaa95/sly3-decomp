// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// CRef equality (recursive). Adapted from the matched Sly 2 source src/hand/func_001205B8.cpp (Sly 3: -Os, short tags 2 lower, new node layouts).
struct NODE;
struct CRef {
    short m_tagk; short m_pad;
    union { int n; void *pv; NODE *pnode; struct W *pw; struct X *px; } u;
    CRef() { m_tagk = -1; }
    CRef(int n, int tagk) { u.n = n; m_tagk = tagk; }
    CRef(NODE *p) __asm__("func_0012B1D8");
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct NODE { CRef ref; int n8; NODE *pnext; };
struct W { int cref; int n4; int n8; int nC; int n10; int n14; NODE *pnext; };
struct X { int cref; int n4; int n8; int nC; int n10; };

extern "C" CRef func_00122220(const CRef &a, const CRef &b);
CRef func_00122220(const CRef &a, const CRef &b)
{
    int f;
    if (a.m_tagk != b.m_tagk) {
        f = 0;
    } else {
        switch (a.m_tagk) {
        case 0x1D: {
            NODE *pa = a.u.pnode;
            NODE *pb = b.u.pnode;
            if (pa == pb) {
                f = 1;
            } else if ((pa->pnext == 0) != (pb->pnext == 0)) {
                f = 0;
            } else {
                CRef r;
                r = func_00122220(pa->ref, pb->ref);
                if (r.u.n == 0) {
                    f = 0;
                } else if (pa->pnext == 0) {
                    f = 1;
                } else {
                    CRef ra(pa->pnext);
                    CRef rb(pb->pnext);
                    r = func_00122220(ra, rb);
                    f = r.u.n;
                }
            }
            break;
        }
        case 0x1E: {
            W *pa = a.u.pw;
            W *pb = b.u.pw;
            if (pa == pb) {
                f = 1;
            } else if (pa->nC != pb->nC) {
                f = 0;
            } else if (pa->n10 != pb->n10) {
                f = 0;
            } else if (pa->n8 != pb->n8) {
                f = 0;
            } else {
                CRef ra(pa->pnext);
                CRef rb(pb->pnext);
                f = func_00122220(ra, rb).u.n;
            }
            break;
        }
        case 0x13: case 0x15: case 0x16: case 0x17: case 0x1F:
            f = a.u.n == b.u.n;
            break;
        case 0x20: {
            X *pa = a.u.px;
            X *pb = b.u.px;
            if (pa == pb) {
                f = 1;
            } else {
                f = pa->nC == pb->nC && pa->n10 == pb->n10;
            }
            break;
        }
        case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
        case 0x22:
            f = 1;
            break;
        }
    }
    return CRef(f, 0x15);
}
