// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x6C]; int x6C; char pad2[0x9C - 0x70]; float f9C; float fA0; };
struct G { char pad[0x14]; struct X *x14; char pad1[4]; float f1C; char pad2[0x30 - 0x20]; int x30; char pad3[0x7CD4 - 0x34]; int mode; };
struct R { char pad[0xC8]; int xC8; };
extern struct G D_004BC230;
extern struct R *D_004794C4;
extern char D_00475480[];
void *func_00150630(void *p, int id);
void func_00271730(void *p, void *q);
void func_00271828(void *p, char *buf);
void func_00283620(struct X *x, float g, char *buf);
void func_00284FC8(void *p)
{
    char buf[0x20];
    int id;
    switch (D_004BC230.mode) {
    case 2:
    case 3:
        id = D_004BC230.x30;
        if (id == -1) {
            id = D_004794C4->xC8;
            if (id == -1)
                id = D_004BC230.x14->x6C;
        }
        func_00271730(p, func_00150630(D_00475480, id));
        break;
    case 4:
    case 6:
        if (D_004BC230.x14->fA0 != 0.0f) {
            func_00283620(D_004BC230.x14, D_004BC230.f1C, buf);
            func_00271730(p, func_00150630(D_00475480, 0x1EF));
            func_00271828(p, buf);
        } else if (D_004BC230.x14->f9C != 0.0f) {
            func_00283620(D_004BC230.x14, D_004BC230.f1C, buf);
            func_00271730(p, func_00150630(D_00475480, 0x1F3));
            func_00271828(p, buf);
        } else {
            func_00271730(p, func_00150630(D_00475480, 0x1F4));
        }
        break;
    }
}
