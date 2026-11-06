// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct S { char pad[0x4C]; void *p4C; char pad2[0x1B4 - 0x50]; int n1B4; int pad1B8; float f1BC; M3 m; };
extern qword D_00317550;
M3 *func_0011C8C0(M3 *pm, qword v);
void func_0028F260(struct S *);
void func_0024E878(struct S *p, float f)
{
    if (!p->n1B4) {
        M3 m;
        p->f1BC = f;
        func_0011C8C0(&m, D_00317550);
        p->m = m;
        if (p->p4C)
            func_0028F260(p);
    }
}
