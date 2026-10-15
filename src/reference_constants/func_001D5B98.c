// Reference algorithm: src/hand/func_001B0D90.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(void *, qword); };
struct S { char pad[0xC]; struct VTE *vt; char pad1[0x14C - 0x10]; void *p16C; int pad2; float f174; float f178; };
void func_001D65A8(struct S *p, float g);
void func_001D6110(struct S *p, int f);
float func_0022DFA0(void *p);
float func_0022F3F8(void *p);
void func_0022E148(void *p, float g, qword *pv, int n);
void func_001D5B98(struct S *p)
{
    qword v;
    func_001D65A8(p, 1.0f);
    if (p->p16C) {
        func_001D6110(p, 1);
        p->f174 = func_0022DFA0(p->p16C);
        p->f178 = func_0022F3F8(p->p16C);
        func_0022E148(p->p16C, p->f174, &v, 0);
        p->vt[34].pfn((char *)p + p->vt[34].d, v);
    } else {
        func_001D6110(p, 0);
    }
}
