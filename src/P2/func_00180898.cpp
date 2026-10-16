// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
extern void *D_0036C2D0[];
int func_00180850(unsigned short key);
}
extern "C" void *func_00180898(int key)
{
    int index = func_00180850((unsigned short)key);
    if (index != -1)
        return D_0036C2D0[index];
    return 0;
}
