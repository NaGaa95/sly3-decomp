// Reference: Sly 2 src/hand/func_00118FB0.cpp; target Sly 3 0x002B9EA8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VUF { qword q; VUF() __asm__("func_002BA000"); };
struct NODE { NODE *pnodeLeft; NODE *pnodeRight; qword *pplane; };
static inline NODE *PnodeCheck(NODE *p, NODE *pnodeMax)
{
    if (!(p < pnodeMax))
        p = 0;
    return p;
}
extern "C" NODE *func_002B9EA8(NODE *pnode, NODE *pnodeMax, qword pos)
{
    NODE *p;
    if (pnode) do {
        qword plane = *pnode->pplane;
        VUF d;
        VUF one;
        qword dq;
        register qword oq __asm__("vf1"); /* pin: the one-vector gets vf1, the dot result vf2 */
        float g;
        __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddaz.x $ACC, %0, %1z\n\tvmsubw.x %1, %0, %2w"
                : "=&j"(oq), "=&j"(dq) : "j"(plane), "j"(pos));
        { int t; __asm__("qmfc2.ni %0, %2\n\tmtc1 %0, %1" : "=&r"(t), "=f"(g) : "j"(dq)); }
        one.q = oq;
        d.q = dq;
        if (g < -1.0e-4f) {
            NODE *q = PnodeCheck(pnode->pnodeLeft, pnodeMax);
            if (!q)
                return pnode;
            pnode = q;
        } else if (g > 1.0e-4f) {
            NODE *q = PnodeCheck(pnode->pnodeRight, pnodeMax);
            if (!q) return 0;
            pnode = q;
        } else {
            NODE *r = PnodeCheck(pnode->pnodeRight, pnodeMax);
            if (r) {
                r = func_002B9EA8(r, pnodeMax, pos);
                if (r) return r;
            }
            NODE *q = PnodeCheck(pnode->pnodeLeft, pnodeMax);
            if (!q)
                return pnode;
            pnode = q;
        }
    } while (pnode);
    return 0;
}
