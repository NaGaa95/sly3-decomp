// Sly 2 reference: src/hand/func_00217F38.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct Y { char pad[0x30]; void *x30; char pad2[0x3C]; };
struct F { int c; struct Y *ay; char pad[0x10]; };
struct S { int x0; int x4; struct F *af; };
void func_002646F8(void *p, struct Y *y);
void func_002643F8(struct Y *y);
static inline void UpdateAy(int n, struct Y *ay)
{
    int k; for (k = 0; k < n; k++) { struct Y *y = &ay[k]; if (y->x30) func_002646F8(y->x30, y); else func_002643F8(y); }
}
void func_002672B8(struct S *p, int i)
{
    UpdateAy(p->af[i].c, p->af[i].ay);
}
