// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// True if pos touches one of the entries: inside its radius (flag 0x20000) or inside its hull (+0x84).
typedef int qword __attribute__((mode(TI)));
typedef unsigned int DIU __attribute__((mode(DI)));
struct OWN { char pad[0x70]; qword pos; char pad80[0x24]; int nA4; };
struct E
{
    struct OWN *pown;
    char pad4[4];
    float r;
    char padC[0xC];
    DIU grf;
    char pad20[0x84 - 0x20];
    void *phull;
    char pad88[0xC0 - 0x88];
    int nC0;
    char padC4[0xD0 - 0xC4];
};
struct S { char pad[0xD0]; int ce; struct E *ae; };
void func_0018B1E0(struct E *pe);
int func_00119C90(void *phull, int n, qword pos);
static inline float SqDist(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "0"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
int func_00240850(struct S *p, qword pos)
{
    int i;
    for (i = 0; i < p->ce; i++) {
        struct E *pe = &p->ae[i];
        int f;
        if (pe->grf & 0x80000)
            continue;
        if (pe->grf & 0x20000) {
            f = SqDist(pos, pe->pown->pos) < pe->r * pe->r;
            if (f)
                return 1;
        }
        if (pe->phull) {
            if (pe->nC0 != pe->pown->nA4)
                func_0018B1E0(pe);
            if (func_00119C90(pe->phull, 0x7FFFFFFF, pos))
                return 1;
        }
    }
    return 0;
}
