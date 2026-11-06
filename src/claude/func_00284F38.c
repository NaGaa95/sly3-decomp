// SLY3_CFLAGS: -Os -G0
struct G { char pad[0x30]; int x30; char pad2[0x7CD4 - 0x34]; int mode; };
extern struct G D_004BC230;
extern char D_00475480[];
void *func_00150630(void *p, int id);
void func_00271730(void *p, void *q);
void func_00284F38(void *p)
{
    int id = -1;
    switch (D_004BC230.mode) {
    case 2: case 3: id = 0x1EC; break;
    case 4: case 6: id = 0x1EB; break;
    case 5: id = D_004BC230.x30; break;
    }
    if (id != -1)
        func_00271730(p, func_00150630(D_00475480, id));
}
