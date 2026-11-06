// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; int (*fn)(void *, int, float); };
struct Owner { char pad0[0x2C]; struct VTE *vt; };
struct E { float t; int n4; int n8; int n0C; int n10; int n14; int n18; };
struct Item { float t; char pad4[0x1C]; int n20; char pad24[0xC]; };
struct S {
    char pad0[0x134]; struct Owner *owner;
    char pad138[0x198 - 0x138]; float g198;
    char pad19C[0x1A0 - 0x19C]; int c1A0;
    char pad1A4[0x1B0 - 0x1A4]; struct Item items[1];
    char pad1E0[0x3C0 - 0x1E0]; int c3C0; struct E a3C4[3];
    int n418; char pad41C[0x480 - 0x41C]; float g480; float g484; float g488;
};
extern char D_00474FF0[];
extern char D_0036C700[];
float func_002483D8(void *);
struct E *func_0020ADF0(struct S *, int);
void func_0020AE20(struct S *, int, int, int);
void func_0020AC40(struct S *, float);
float func_0020AC38(struct S *, float);
float func_0020ABA0(struct S *, struct E *);
int func_001A7A80(struct Owner *, int, float);
void func_001854C8(void *, int, struct S *);
void func_0020A930(struct S *p)
{
    float t;
    int i;
    struct E *e, *next;
    p->n418 = p->owner->vt[1].fn((char *)p->owner + p->owner->vt[1].d, 0xF0, 0.0f);
    if (!p->n418)
        return;
    t = func_002483D8(D_00474FF0);
    for (i = 0; i < p->c3C0; i++) {
        e = &p->a3C4[i];
        if (e->n18)
            continue;
        func_001854C8(D_0036C700, 0x48, p);
        if (t < e->t - p->g198) {
            func_0020AE20(p, 2, e->n4, p->n418);
            func_0020AC40(p, p->g480);
            break;
        }
        if (e->n14) {
            next = func_0020ADF0(p, i);
            if (next && next->t - p->g198 < t) {
                e->n18 = 1;
                e = next;
            } else {
                func_0020AE20(p, 3, e->n4, p->n418);
                func_0020AC40(p, p->g488);
                break;
            }
        }
        e->n14 = 1;
        if (func_001A7A80(p->owner, e->n4, 0.0f)) {
            func_0020AE20(p, 4, e->n4, p->n418);
            func_0020AC40(p, func_0020AC38(p, func_0020ABA0(p, e)));
            {
                int j;
                for (j = 0; j < p->c1A0; j++) {
                    struct Item *it = &p->items[j];
                    if (__builtin_fabsf(it->t - e->t) < 0.1f) {
                        it->n20 = 1;
                        break;
                    }
                }
            }
        } else {
            func_0020AE20(p, 5, e->n4, p->n418);
            func_0020AC40(p, p->g484);
        }
        break;
    }
}
