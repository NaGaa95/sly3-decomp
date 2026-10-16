// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" unsigned short D_00344FB0[3];
extern "C" int func_00180850(unsigned short code)
{
    for (int index=0; index<3; ++index)
        if (code==D_00344FB0[index])
            return index;
    return -1;
}
