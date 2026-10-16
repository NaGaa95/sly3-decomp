// SLY3_CFLAGS: -Os -G0
struct IndexedControl { char unknown_0[0x190]; int primary[2]; int limit[2]; };
int func_00215860(struct IndexedControl *control,int index)
{
    return control->limit[index];
}
