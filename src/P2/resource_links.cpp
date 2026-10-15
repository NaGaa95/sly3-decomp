// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "heap.h"

struct LinkedResource40 { int id; unsigned char opaque[36]; };
struct LinkedResource32 { int id; unsigned char opaque[28]; };
struct ResourceLinks20 {
    unsigned char prefix[6];
    unsigned char resource40_count;
    unsigned char resource32_count;
    void *owner;
    LinkedResource40 **resources40;
    LinkedResource32 **resources32;
};
typedef char Resource40Stride[(sizeof(LinkedResource40)==40)?1:-1];
typedef char Resource32Stride[(sizeof(LinkedResource32)==32)?1:-1];
typedef char ResourceLinksSize20[(sizeof(ResourceLinks20)==20)?1:-1];
extern "C" {
    extern LinkedResource40 *D_00474F9C;
    extern LinkedResource32 *D_00474FA4;
    void func_00118DA0(void *stream,int bytes,void *output);
    unsigned int func_00119048(void *stream);
}

extern "C" void func_00234900(void *stream,HEAP *heap,ResourceLinks20 *links)
{
    int i;
    func_00118DA0(stream,8,links);
    if(links->resource40_count) {
        links->resources40=(LinkedResource40 **)heap->PvAlloc(links->resource40_count*4,0x2F);
        for(i=0;i<links->resource40_count;i++)
            links->resources40[i]=&D_00474F9C[func_00119048(stream)];
    }
    if(links->resource32_count) {
        links->resources32=(LinkedResource32 **)heap->PvAlloc(links->resource32_count*4,0x2F);
        for(i=0;i<links->resource32_count;i++) {
            int index=func_00119048(stream);
            if(index==0xFFFF)links->resources32[i]=0;
            else links->resources32[i]=&D_00474FA4[index];
        }
    }
}
