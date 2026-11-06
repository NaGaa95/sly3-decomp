// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_00219348.c.
struct Y { char pad[0x30]; void *x30; int n34; char pad38[0x61 - 0x38]; unsigned char b61; char pad62[0x70 - 0x62]; };
struct F { int x0; struct Y *ay; char pad[0x10]; };
struct Q { char pad[8]; struct F *af; };
struct E { int x0; unsigned char c4, c5, c6; char pad7[5]; unsigned char *pc; };
struct S { int x0; struct E *ae; char pad8[4]; struct Q *pq; };
void func_002646F8(void *p, struct Y *y);
void func_002643F8(struct Y *y);
void func_002685B0(struct S *p, int i, int j)
{
    struct E *e = &p->ae[i];
    struct Y *ay = p->pq->af[j].ay;
    unsigned int k;
    for (k = 0; k < e->c6; k++) {
        int idx;
        struct Y *y;
        unsigned char *pcb = e->pc;
        pcb += e->c4 * 0x30;
        pcb += e->c5 * 8;
        idx = pcb[k];
        y = &ay[idx];
        if (y->n34 == 1)
            ay[idx + y->b61].n34 = 0;
        if (y->x30)
            func_002646F8(y->x30, y);
        else
            func_002643F8(y);
    }
}
