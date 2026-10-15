// Recovered typed shuffle-array initialization and pointer choice/refill.
// The last previous value is excluded from the first position after reshuffling.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "shuffle_array.h"
template<class T>static inline void InitShuffleArray(SHUFFLE_ARRAY_FIELDS<T> *array,int count,const T *values,HEAP *heap) {
    if(array->heap)array->heap->Free(array->values);
    array->heap=heap;array->count=count;
    array->values=(T *)PvAllocCopy(heap,count*sizeof(T),(void *)values,4);
    array->cursor=0;
    ShuffleArray(array->count,array->values);
}
extern "C" void func_002BDE20(SHUFFLE_ARRAY_FIELDS<int> *array,int count,const int *values,HEAP *heap) {InitShuffleArray(array,count,values,heap);}
extern "C" void func_002BDFB0(SHUFFLE_ARRAY_FIELDS<void *> *array,int count,void *const *values,HEAP *heap) {InitShuffleArray(array,count,values,heap);}
extern "C" void *func_002B4FF0(SHUFFLE_ARRAY_FIELDS<void *> *array) {
    if(array->cursor==array->count) {ShuffleArray(array->count,array->values);array->cursor=0;}
    return array->values[array->cursor++];
}
