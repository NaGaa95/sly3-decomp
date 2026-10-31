// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct E { char pad[0x18]; float *ag; char pad2[0x28 - 0x1C]; };
struct F { char pad[0x54]; qword *av; char pad2[0x60 - 0x58]; };
struct DL { void *a, *b; int c; };
struct DZG { int x0; int c; struct E *ae; char pad[0x30 - 0xC]; struct DL dl; char pad2[0x60 - 0x3C]; struct F *af; };
struct Y { char pad[0xA8]; int i; };
struct X { char pad[0x40]; qword v; struct Y *py; };
void func_0011AF60(struct DL *pdl, void *pv);
static __inline__ int Dot(qword a, qword b)
{
    qword r, one;
    int g;
    __asm__("vmul.xyz %0, %0, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(r), "=j"(one) : "0"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
void func_001758A0(struct DZG *pdzg, void *pdz, struct X *px)
{
    int i;
    int k = px->py->i;
    for (i = 0; i < pdzg->c; i++) {
        struct E *pe = &pdzg->ae[i];
        int *ag = (int *)pe->ag;
        __asm__ __volatile__("" ::: "memory");
        if (ag) {
            {
                struct F *pf = &pdzg->af[i];
                register int off asm("$4") = k * 16; /* register pin: keeps k*16 in a0 */
                ag[pdzg->c] = Dot(px->v, *(qword *)(off + (int)pf->av));
            }
        }
    }
    func_0011AF60(&pdzg->dl, pdz);
    pdzg->c++;
}
