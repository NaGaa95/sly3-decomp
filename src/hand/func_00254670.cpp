#include "heap_frame_api.h"
// Native actor/action eligibility; actual flag bit56 and real count/node-array collider outputs.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct L {
    char opaque0[0x28];
    unsigned long flags28;
};
struct T {
    char opaque0[0x40];
    int k;
};
struct F64 {
    char opaque0[0x3C8];
    L *pl;
};
struct O;
struct MATRIX4 {
    qword row[4];
};
struct VE {
    short delta,padding;
    const MATRIX4 *(*matrix)(void *);
};
struct S2 {
    char opaque0[0xC];
    VE *table;
    char opaque10[0xDC-0x10];
    void *pEC;
    char opaqueE0[0x1008-0xE0];
    int nE68;
    char opaque100C[0x10D0-0x100C];
    F64 *pF64;
};
struct O {
    char pad[0x14];
    T *pt;
    char pad1[0x20-0x18];
    qword pos;
    char pad2[0x40-0x30];
    S2 *p40;
    void *p44;
    char pad3[0x54-0x48];
    int k54;
};
inline qword Position(S2 *p) {
    VE *entry=&p->table[36];
    return entry->matrix((char *)p+entry->delta)->row[3];
}
struct NODE;
struct HIT;
typedef int (*FILTER)(void *,NODE *);
extern "C" {
    int func_00254818(S2 *p);
    void *func_00170528(F64 *p, void *x);
    int func_00173B70(O *o, qword q);
    int func_0027F258(L *pl, qword q);
    void func_0025CF18(void *g, qword a, qword b, FILTER filter, void *context, int *count, NODE ***nodes);
    NODE *func_00165000(int flags, qword a, qword b, int count, NODE **nodes, HIT *output);
    int func_0025CE90(void *context,NODE *node);
    extern char D_00475480[];
    int func_00254670(S2 *p, O *o);
}
class FRAME;
class FRAME {
    void *marker;
    public: FRAME() asm("func_001D2770");
    ~FRAME() {
        func_001D2798(this,2);
    }
};
int func_00254670(S2 *p, O *o) {
    T *pt;
    qword pos, tpos;
    if (!func_00254818(p)) return 0;
    if (o->k54 < p->nE68) return 0;
    if (o->p40 && o->p40 == p) return 0;
    if (o->k54 == 4) {
        void *x = o->p44;
        void *e = func_00170528(p->pF64, x);
        if (x != p && !e) return 0;
    }
    pt = o->pt;
    pos = Position(p);
    tpos = o->pos;
    switch (pt->k) {
        case 0: return func_00173B70(o, Position(p));
        case 1: {
            L *pl = p->pF64->pl;
            if (!pl || ((int)(pl->flags28 >> 56) & 1) == 0) return 0;
            if (!func_0027F258(pl, tpos)) return 0;
            {
                FRAME frame;
                int count;
                NODE **nodes;
                func_0025CF18(D_00475480, pos, tpos, func_0025CE90, p->pEC, &count, &nodes);
                if (!func_00165000(0, pos, tpos, count, nodes, 0)) return 1;
                return 0;
            }
        }
    }
    return 0;
}
