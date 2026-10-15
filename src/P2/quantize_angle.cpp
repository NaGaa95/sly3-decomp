// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" float func_0011E3B8(float radians);
// Original count0 passthrough/count1 zero; accepted subdivisions are nonnegative.
extern "C" float func_0011E438(float radians,int subdivisions)
{
    if (subdivisions==0) return radians;
    if (subdivisions==1) return 0.0f;
    radians=func_0011E3B8(radians);
    float spacing=6.28318530718f/subdivisions;
    float half=spacing*0.5f;
    float sign=1.0f;
    if (radians<0.0f) {
        radians=-radians;
        sign=-1.0f;
    }
    float snapped;
    int last=subdivisions/2;
    for (int i=0;i<=last;i++) {
        snapped=spacing*i;
        if (snapped-half<=radians && radians<=snapped+half)
            break;
    }
    return snapped*sign;
}
