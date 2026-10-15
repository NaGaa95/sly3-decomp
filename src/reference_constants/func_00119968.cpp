// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Read a counted raw16-bit key through the original optional heap interface.
#include "../../src/P2/heap.h"
struct ArchiveLookupKey { int unitCount; unsigned short *units; };
typedef char KeySize[(sizeof(ArchiveLookupKey)==8)?1:-1];
extern "C" unsigned int func_00119048(void *stream);
extern "C" void func_00118DA0(void *stream,int bytes,void *destination);
extern "C" void func_00119968(void *stream,ArchiveLookupKey *key,void *heap) {
    int count=func_00119048(stream);
    void *units=0;
    if(heap) units=((HEAP *)heap)->PvAlloc(count*sizeof(unsigned short),0x37);
    if(key) {
        key->unitCount=count;
        key->units=(unsigned short *)units;
    }
    func_00118DA0(stream,count*sizeof(unsigned short),units);
}
