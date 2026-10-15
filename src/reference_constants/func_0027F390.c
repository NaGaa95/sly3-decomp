#include "heap_frame_api.h"
// Reference algorithm: src/hand/func_00227D20.c; Sly 3 identity is canonical.
// The outerF12 gain remains a realinput used for comparison and119C20.
// Fastpath27F258 receives objectA0/fullTIpointA1; originalF12 remains ambient,
// with no explicitcall-siteFP setup and no transitiveFPR consumption.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct MSG {
    int cb;
    int nKind;
}
MSG;
typedef struct MARK {
    int a[4];
}
MARK;
struct S {
    char pad[0xD4];
    int c;
    int pad1;
    void *pEC;
};
static __inline__ int Min(int a, int b) {
    return a < b ? a : b;
}
int func_0027F258(struct S *p, qword point);
void *func_001D25B0(MSG *pmsg);
qword func_001C9428(void *first, struct S *second, qword point);
int func_00119C20(void *p, int n, qword v, int *pc, void **ppv, float g);
int func_0027F390(struct S *p, qword v, float g) {
    if (g <= 1.0f) {
        return func_0027F258(p, v);
    }
    else {
        MARK mark;
        int f = 0;
        MSG msg;
        int c;
        void *pv;
        func_001D2770(&mark);
        {
            int cT = p->c;
            MSG *pm = &msg;
            cT = Min(cT, 0x1555);
            c = cT;
            pm->cb = cT * 12;
            pm->nKind = 0x10;
            pv = func_001D25B0(pm);
        }
        {
            int r = func_00119C20(p->pEC, 0x7FFFFFFF, func_001C9428(0, p, v), &c, &pv, g);
            if (r == 0 || r == 2) f = 1;
        }
        func_001D2798(&mark, 2);
        return f;
    }
}
