// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct L { char pad[0x1114]; int x1114; };
struct F { int x0; int x4; int x8; };
struct E {
    int ak[6][2];
    char pad[0x30 - 0x30];
    char list[0x10];
    int x40; int x44;
    char pad2[0x84 - 0x48]; int x84;
    char pad3[0xE4 - 0x88]; int cF; struct F *aF;
    char pad4[0xF0 - 0xEC];
};
struct S { char pad[0x4C]; struct L *pl; char pad2[0x5C - 0x50]; int c; struct E *ae; };
extern char D_00475480[];
void func_001C7DC8(struct S *p);
struct L *func_0017E5D8(void *g, int a, int b, struct S *p);
int func_0017E1B8(void *g, int k, int v, struct S *p);
int func_0013B500(int o, int k);
void func_00258930(void *pl, struct L *l, int x);
void func_00258958(void *pl);
void func_001728F0(struct S *p)
{
    int i;
    func_001C7DC8(p);
    p->pl = func_0017E5D8(D_00475480, 3, 0x33, p);
    for (i = 0; i < p->c; i++) {
        struct E *e = &p->ae[i];
        int j, n;
        {
            int *pk = e->ak[0];
            for (j = 5; j >= 0; j--) {
                int k = pk[0];
                pk[0] = 0;
                if (k != 0 && k != -1) {
                    int o = func_0017E1B8(D_00475480, 4, k, p);
                    if (o) {
                        if (func_0013B500(o, 0x82))
                            pk[0] = o;
                        else if (func_0013B500(o, 0x84))
                            pk[1] = o;
                    }
                }
                pk += 2;
            }
        }
        func_00258930(e->list, p->pl, p->pl->x1114);
        e->x44 = *(int *)((char *)e + 0x8);
        *(int *)((char *)e + 0x84) = *(int *)((char *)e + 0x10);
        func_00258958(e->list);
        for (n = 0; n < e->cF; n++) {
            struct F *f = &e->aF[n];
            int k = f->x4;
            if (k == 0 || k == -1)
                f->x4 = (int)p->pl;
            else
                f->x4 = func_0017E1B8(D_00475480, 4, k, p);
        }
    }

}
