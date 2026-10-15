// Sly 2 reference: src/hand/func_00161F48.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct E { int oid; int n; };
extern char D_00475480[];
void *func_0017E1B8(void *pg, int kind, int oid, void *owner);
void func_00189078(void *p, int n, void *owner);
void func_00185908(void *pv, int c, struct E *ae, void *owner)
{
    int i;
    for (i = 0; i < c; i++) {
        void *p = func_0017E1B8(D_00475480, 0x105, ae[i].oid, owner);
        if (p)
            func_00189078(p, ae[i].n, owner);
    }
}
