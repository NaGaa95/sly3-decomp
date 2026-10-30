// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00137F60: adapted from the matched Sly 2 source src/hand/func_00130F88.cpp (Sly 3 offsets; times are re-read).
struct E { float t; int k; int x8; int xC; int x10; };
struct Q { char pad[0x90]; int c; struct E *ae; };
struct B { int pad[3]; virtual void Begin(); virtual void End(); };
struct P : B { int x10; struct Q *pq; int x18; float g1C; float g20; char pad2[0x40 - 0x24]; float g40;
    char pad3[0x50 - 0x44]; int i50; };
struct G { P *p; G(P *pp) : p(pp) { p->Begin(); } ~G() { p->End(); } };
extern "C" {
void func_00138270(struct P *p, struct E *pe);
int func_00138AC8(struct P *p);
}
extern "C" void func_00137F60(struct P *p)
{
    if (p->pq->c) {
    G g(p);
    p->g20 = p->g1C;
    while (!func_00138AC8(p)) {
        struct Q *pq = p->pq;
        int i = p->i50;
        if (i < pq->c) {
            struct E *pe;
            if ((pq->ae[i].t < p->g20 || (p->g20 == pq->ae[i].t && 0.0f < p->g40)) && (pe = &pq->ae[i], 1)) {
                p->i50 = i + 1;
                func_00138270(p, pe);
                continue;
            }
        }
        if (i > 0 && (p->g20 < pq->ae[i - 1].t || (p->g20 == pq->ae[i - 1].t && p->g40 < 0.0f))) {
            p->i50 = i - 1;
            func_00138270(p, &pq->ae[p->i50]);
        } else {
            p->g1C = p->g20;
            break;
        }
    }
    }
}
