// Reference: Sly 2 src/hand/func_00118A88.cpp; target Sly 3 0x002B9230.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VUF { qword q; VUF() __asm__("func_002BA000"); };
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
extern NODE D_00341DF0;
extern NODE D_00341E00;
static inline NODE *PnodeCheck(NODE *p, NODE *pnodeMax)
{
    if (!(p < pnodeMax))
        p = 0;
    return p;
}
extern "C" int func_002B9230(NODE *pnode, NODE *, qword pos, float eps, int *pcnode, NODE **ppnode)
{
    float g;
    while (pnode) {
        qword plane = *pnode->pplane;
        VUF d;
        VUF one;
        qword dq;
        register qword oq __asm__("vf1"); /* pin: the one-vector gets vf1, the dot result vf2 */
        __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddaz.x $ACC, %1, %0z\n\tvmsubw.x %0, %1, %2w"
                : "=&j"(dq), "=&j"(oq) : "j"(plane), "j"(pos));
        int n;
        __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(n), "=f"(g) : "j"(dq));
        one.q = oq;
        d.q = dq;
        if (g > eps) {
            pnode = pnode->pnodeRight;
        } else if (g < -eps) {
            pnode = pnode->pnodeLeft;
        } else {
            int nl, nr;
            NODE *pl = pnode->pnodeLeft;
            if (pl) {
                nl = func_002B9230(pl, 0, pos, eps, pcnode, ppnode);
                pl = *ppnode - 1;
            } else {
                nl = 0;
            }
            NODE *pr = pnode->pnodeRight;
            if (pr) {
                nr = func_002B9230(pr, 0, pos, eps, pcnode, ppnode);
                pr = *ppnode - 1;
            } else {
                nr = 1;
            }
            if (nl == nr && nr != 2)
                return nr;
            if (*pcnode <= 0)
                return 1;
            NODE *pn = (*ppnode)++;
            (*pcnode)--;
            pn->pplane = pnode->pplane;
            switch (nl) {
            case 0: pn->pnodeLeft = 0; break;
            case 1: pn->pnodeLeft = &D_00341DF0; break;
            case 2: pn->pnodeLeft = pl; break;
            }
            switch (nr) {
            case 0: pn->pnodeRight = &D_00341E00; break;
            case 1: pn->pnodeRight = 0; break;
            case 2: pn->pnodeRight = pr; break;
            }
            return 2;
        }
    }
    return g > 0.0f;
}
