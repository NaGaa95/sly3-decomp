// Reference algorithm: src/hand/func_001E93F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void *pfn; };
struct LO { int pad[3]; struct VTE *pvt; };
struct M4 { qword r[3]; qword pos; };
struct P { int pad[4]; struct LO *apo[4]; qword apos[2]; void *ap40[2]; int a48; };
extern char D_0034A160[];
float func_0022DFA0(int);
float func_0022DFC0(int);
void func_0022E148(int, qword *, int, float);
void func_00231078(struct P *p, int i, struct LO *po)
{
    p->apo[i] = po;
    if (po) {
        struct M4 m;
        struct VTE *pe = &po->pvt[37];
        p->ap40[i] = ((void *(*)(void *, struct M4 *))pe->pfn)((char *)po + pe->d, &m);
        *(p->apos + i) = m.pos;
    } else {
        float f;
        p->ap40[i] = D_0034A160;
        if (i == 0)
            f = func_0022DFA0(p->a48);
        else
            f = func_0022DFC0(p->a48);
        func_0022E148(p->a48, &p->apos[i], 0, f);
    }
}
