// Recovered signed-ID membership scan; a missing current ID or empty list accepts.
// The compiler jump alignment reproduces the original skipped alignment NOP.
// SLY3_CFLAGS: -Os -malign-jumps=3 -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" int func_0025E150();
extern "C" int func_00151C98(int count,const short *values) {
    int id=func_0025E150();
    if(id==-1)return 1;
    if(!count)return 1;
    const short *scan=values;
    int i=0;
    goto condition;
next:
    ++i;
condition:
    if(i>=count)return 0;
    if(*scan++!=id)goto next;
    return 1;
}
