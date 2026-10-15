// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct O { char pad[0x40]; M4 mat; };
void func_0011D768(M4 *pmDst, M4 *pmSrc);
void func_0011D558(M4 *pmDst, M4 *pmA, M4 *pmB);
void *func_00291E8C(void *d, void *s, int n);
M4 *func_0028EC08(M4 *pr, struct O *pa, struct O *pb, M4 *pm)
{
    M4 m, mT, mInv;
    if (pa) {
        M4 *pmA;
        if (pb) {
            M4 *pmT = &mT;
            func_0011D768(&mInv, &pb->mat);
            func_0011D558(pmT, &mInv, &pa->mat);
            pmA = pmT;
        } else {
            pmA = &pa->mat;
        }
        func_0011D558(&m, pmA, pm);
        func_00291E8C(pr, &m, 0x40);
    } else if (pb) {
        func_0011D768(&mT, &pb->mat);
        func_0011D558(&m, &mT, pm);
        func_00291E8C(pr, &m, 0x40);
    } else {
        func_00291E8C(pr, pm, 0x40);
    }
    return pr;
}
