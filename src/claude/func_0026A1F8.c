// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { int dn; int snd; float dt; };
struct S { char pad[0x94]; int n94; char pad2[0x120 - 0x98]; int n120; float f124; };
extern struct E D_00327FC0[3];
extern float D_0036BBD8;
extern char D_0036C700[];
extern char D_00475480[];
void func_00261250(struct S *);
int func_001852E0(void *);
int func_00262128(void *, int);
void func_0026A1C8(struct S *);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_00261030(struct S *);
void func_0026A1F8(struct S *p)
{
    int d;
    func_00261250(p);
    d = func_001852E0(D_0036C700) - p->n120;
    if (func_00262128(D_00475480, p->n94) || d <= 0) {
        func_0026A1C8(p);
        return;
    }
    {
    float t = D_0036BBD8;
    if (p->f124 < t) {
        int i;
        struct E *e;
        if (d > 200)
            i = 2;
        else
            i = d > 20;
        e = &D_00327FC0[i];
        p->n120 += e->dn;
        p->f124 = t + e->dt;
        func_00244F08(func_002459F8(e->snd), 0);
    }
    }
    func_00261030(p);
}
