// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Y { char pad[0x1108]; int x1108; char pad1[0x11C0 - 0x110C]; };
struct Z { char pad[0xD0]; int xD0; };
struct S { struct Z *p0; };
extern struct Y D_0036E740[];
extern char D_0036E6D0[];
struct Z *func_001A91D8(struct Y *py);
int func_001A9760(struct Y *py);
void *func_00169EB0(struct S *p)
{
    int i = p->p0->xD0;
    struct Y *py;
    if (i != -1) {
        py = &D_0036E740[i];
        if (py->x1108 == 0 && func_001A91D8(py) == p->p0) {
            if (!func_001A9760(py))
                goto found;
        }
    }
    return D_0036E6D0;
found:
    return py;
}
