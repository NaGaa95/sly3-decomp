// Sly 2 reference: src/hand/func_00227820.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct P { int id; };
struct Q { unsigned short *p0; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
extern char D_00474FF0[];
extern char D_003294A0[];
float func_00246E40(void *p, int id);
int func_00264CB0(struct Q *q);
int func_00248858(void *p, int id);
float func_00248898(void *p);
void func_00264D00(struct Q *q, int n);
unsigned short *func_00271828(unsigned short *p, const char *s);
void func_0027EDA8(struct P *p, struct Q *q)
{
    void *pv;
    float f;
    int c, n, fShow;
    if (p->id == -1) return;
    pv = D_00474FF0;
    f = func_00246E40(pv, p->id) - 0.5f;
    c = func_00264CB0(q);
    if (f <= 0.0f || !func_00248858(pv, p->id))
        n = c;
    else
        n = (int)(func_00248898(pv) / f * (float)c);
    if (n < c) {
        func_00264D00(q, n);
        fShow = 1;
    } else {
        fShow = (int)(D_0036BB98.t * 4.0f) & 1;
    }
    if (fShow) func_00271828(q->p0, D_003294A0);
}
