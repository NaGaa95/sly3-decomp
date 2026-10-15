// Sly 2 reference: src/hand/func_00172F10.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
extern float D_00322314;
struct Q2 { qword a, b; };
struct E { qword pos; qword pad; };
struct S { char pad[0x18]; void *p18; char pad2[0x20]; float g3C; char pad3[0x10]; struct E ae[4]; unsigned int cD0; };
int func_001D7F90(void *p);
void func_002B8750(struct Q2 *pq);
void func_001D7FD0(void *p, struct Q2 *pq);
void func_001A7500(struct S *p) {
    void *p18;
    struct E *pe;
    struct Q2 q;
    if (p->cD0 >= 4) return;
    p18 = p->p18;
    if (p->g3C == D_00322314) {
        if (func_001D7F90(p18)) p->g3C = D_0036BB98.t + 1.0f;
    }
    if (D_0036BB98.t < p->g3C) return;
    pe = &p->ae[p->cD0++];
    if (p->cD0 >= 4) p->cD0 = 0;
    func_002B8750(&q);
    q.b = pe->pos;
    func_001D7FD0(p18, &q);
    p->g3C = D_00322314;
}
