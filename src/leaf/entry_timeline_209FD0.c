// SLY3_CFLAGS: -Os -G0
struct E { float t; int n4; int n8; int n0C; int n10; int n14; int n18; };
struct S {
    char pad0[0x190]; int n190; char pad194[0x198 - 0x194]; float g198; float g19C;
    char pad1A0[0x3C0 - 0x1A0]; int c3C0; struct E a3C4[3];
    int n418; char pad41C[0x46C - 0x41C]; float g46C; float g470; char x474[0x18]; float g48C;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
extern char D_00474FF0[];
extern char D_0036C700[];
void func_0023C660(struct S *);
float func_002483D8(void *);
void func_0020AE20(struct S *, int, int, int);
struct E *func_0020ADF0(struct S *, int);
void func_001854C8(void *, int, struct S *);
void func_0020AC40(struct S *, float);
float func_0011E598(void *, float, float, float, int);
void func_0020A930(struct S *);
void func_00209FD0(struct S *p)
{
    float t;
    func_0023C660(p);
    t = func_002483D8(D_00474FF0);
    switch (p->n190) {
    case 1: {
        int j;
        struct E *e;
        for (j = 0; j < p->c3C0; j++) {
            e = &p->a3C4[j];
            if (e->n0C)
                continue;
            if (e->t < t) {
                func_0020AE20(p, 0, e->n4, e->n4);
                e->n0C = 1;
                break;
            }
        }
        break;
    }
    case 2: {
        int i;
        struct E *e, *next;
        func_0020A930(p);
        for (i = 0; i < p->c3C0; i++) {
            e = &p->a3C4[i];
            if (e->n18)
                continue;
            if (!e->n10 && e->t < t) {
                p->n418 = e->n4;
                func_001854C8(D_0036C700, 0x47, p);
                e->n10 = 1;
            }
            next = func_0020ADF0(p, i);
            if (e->n14 && next && next->t - p->g198 < t) {
                e->n18 = 1;
                continue;
            }
            if (e->t + p->g19C < t || (next && next->t < t)) {
                e->n18 = 1;
                if (!e->n14) {
                    func_0020AE20(p, 1, e->n4, -1);
                    func_0020AC40(p, p->g48C);
                }
                break;
            }
        }
        break;
    }
    }
    p->g470 = func_0011E598(p->x474, p->g470, p->g46C, D_0036BB98.dt, 0);
}
