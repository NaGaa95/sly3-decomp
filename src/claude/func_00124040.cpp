// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Script element accessor (Sly 2 func_001222C8 evolved): (elt vec i) / (elt mat i j) / (elt mat i) as a float or row.
// VECTOR/MATRIX4 operator[] inlines give the target register choice with no pins.
typedef int qword __attribute__((mode(TI)));
struct NODE;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; NODE *pnode; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(float g);
    CRef &operator=(qword *pv) __asm__("func_0012B400");
};
struct NODE { CRef ref; int x8; NODE *pnext; };
struct VECTOR { float x, y, z, w; float &operator[](int i) { return (&x)[i]; } };
struct MATRIX4 { VECTOR m[4]; VECTOR &operator[](int i) { return m[i]; } };
extern "C" CRef func_00124040(int c, CRef *aref);
CRef func_00124040(int c, CRef *aref)
{
    CRef ref;
    NODE *pn = aref[1].u.pnode;
    switch (aref[0].m_tagk) {
    case 0x19: {
        int i = pn->ref.u.n;
        if (c == 2) {
            ref = (qword *)&(*(MATRIX4 *)aref[0].u.pv)[i];
        } else {
            pn = pn->pnext;
            ref = (*(VECTOR *)((i << 4) + (int)aref[0].u.pv))[pn->ref.u.n];
        }
        break;
    }
    case 0x18: case 0x1A: case 0x1B:
        ref = (*(VECTOR *)aref[0].u.pv)[pn->ref.u.n];
        break;
    case 0x1C:
        ref = (*(VECTOR *)aref[0].u.pv)[pn->ref.u.n];
        break;
    }
    return ref;
}
/* Next .rodata items of the original unit (FLT_MAX literals read by func_00124228); they follow the jump table. */
extern const float D_0031F4D4, D_0031F4D8;
const float D_0031F4D4 = 3.40282346638528859812e+38f;
const float D_0031F4D8 = 3.40282346638528859812e+38f;
