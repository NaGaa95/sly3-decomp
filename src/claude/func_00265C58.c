// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct E { int x0; int x4; int x8; };
struct O2 { char pad[0x40]; int n40; char pad44[4]; int n48; struct E *ae; int n50; };
struct O { char pad[0x130]; struct O2 *p130; };
struct G { char pad[0x4F68]; struct O *p4F68; };
extern struct G D_00475480;
int func_00235EC8(int);
int func_00265C58(void *unused, int id)
{
    if (id < 0x64F) {
        if (id >= 0x649 && D_00475480.p4F68 && D_00475480.p4F68->p130) {
            struct O2 *o2;
            struct E *e;
            int n = D_00475480.p4F68->p130->n50;
            switch (id) {
            case 0x649:
                n -= 2;
                break;
            case 0x64A:
                n -= 1;
                break;
            case 0x64C:
                n += 1;
                break;
            case 0x64D:
                n += 2;
                break;
            }
            if (n < 0)
                goto none;
            o2 = D_00475480.p4F68->p130;
            if (n >= o2->n48)
                goto none;
            e = &o2->ae[n];
            if (id == 0x64E) {
                if (o2->n40 != 1)
                    goto none;
                id = e->x4;
            } else {
                if (!e->x8)
                    goto none;
                id = e->x0;
            }
            if (id == -1) {
            none:
                return 0;
            }
        }
    }
    return func_00235EC8(id);
}
