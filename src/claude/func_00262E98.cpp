// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct RGBA { unsigned int u; RGBA(unsigned int x) { u = x; } } __attribute__((aligned(16)));
struct QQ { qword a, b; };
struct Z { int x0; int k; char pad8[8]; int id; };
struct Y { int c0; int c1; char pad8[8]; QQ q; Z *pz; char pad34[0x24]; int x58; char pad5c[8]; int x64; int x68; int x6C; };
struct H { int c; Y *ay; char pad8[0x10]; };
struct A { unsigned short c; unsigned short c2; void *ae; H *ah; char padc[0x24]; };
struct S { char pad[0x74]; A *aa; };
extern "C" void func_00267888(A *pa, int i);
extern "C" void func_0011AD68(int *p);
extern "C" int func_00267270(A *pa);
extern "C" void func_00267110(float f, A *pa, int i, int z, void *q, const RGBA &c0, const RGBA &c1);
extern "C" int func_00262E98(S *p, int k, int z, int x, int c, Y *ay)
{
    int i;
    Y *y;
    if (!ay) {
        H *h = p->aa->ah;
        c = h->c;
        ay = h->ay;
    }
    for (i = 0; i < c; i++) {
        Z *pz;
        y = &ay[i];
        pz = y->pz;
        if (!pz || pz->k != 4)
            continue;
        int oldframe=y->x58;
        int id = pz->id;
        if (id == k) {
            if(x != y->x64) continue;
            func_00267888(&p->aa[k], oldframe);
            func_0011AD68(&y->x68);
            y->x58 = func_00267270(&p->aa[k]);
            func_00267110(0.0f, &p->aa[k], z, y->x58, &y->q, RGBA(0x7F7F7F7F), RGBA(0xFFFFFFFF));
            return 1;
        }
        {
            int ah = (int)p->aa[id].ah;
            H *h = (H *)(oldframe * sizeof(H) + ah);
            if (func_00262E98(p, k, z, x, h->c, h->ay))
                return 1;
        }
    }
    return 0;
}
