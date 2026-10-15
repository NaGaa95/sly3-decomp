// Reference algorithm: src/hand/func_0017B690.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct M { int n0; int n4; int n8; };
struct U { char pad[0x40]; void *p40; };
struct T { char pad[0x10CC]; int nF60; };
struct S { char pad[0x10]; struct T *pt; int pad2; struct U *p18; char pad3[0x14]; int n30; };
int func_00254F80(void *p);
int func_00238AD8(struct S *p, int msg, struct M *pm);
int func_001A5750(struct S *p, int msg, struct M *pm) {
    if (msg == 10 && !p->n30 && p->p18->p40 && func_00254F80(p->p18->p40) == pm->n0) {
        switch (pm->n8) {
        case 0x4E: p->pt->nF60 = 1; return 1;
        case 0x4F: p->pt->nF60 = 0; return 1;
        }
    }
    return func_00238AD8(p, msg, pm);
}
