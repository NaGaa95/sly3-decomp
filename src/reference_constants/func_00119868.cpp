// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Read counted 16-bit units into the actual heap and append their zero terminator.
#include "../../src/P2/heap.h"
class CBinaryInputStream;
extern "C" unsigned int func_00119048(void *stream);
extern "C" void func_00118DA0(void *stream,int bytes,void *destination);
extern "C" void func_00119868(CBinaryInputStream *stream,unsigned short **text,HEAP *heap,int allocationKind) {
    int count=func_00119048(stream);
    if(!count) *text=0;
    else {
        unsigned short *units=(unsigned short *)heap->PvAlloc((count+1)*sizeof(unsigned short),allocationKind);
        func_00118DA0(stream,count*sizeof(unsigned short),units);
        units[count]=0;
        *text=units;
    }
}
