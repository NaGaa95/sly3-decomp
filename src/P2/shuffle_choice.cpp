// Recovered virtual shuffle-choice construction and integer selection.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "shuffle_array.h"
extern "C" void func_002BDE20(SHUFFLE_ARRAY_FIELDS<int> *,int,const int *,HEAP *);
SHUFFLE_CHOICE_BASE::SHUFFLE_CHOICE_BASE() {}
SESSION_MENU_ARRAY::SESSION_MENU_ARRAY(int count,const int *values,void *heap):heap(0) {
    func_002BDE20((SHUFFLE_ARRAY_FIELDS<int> *)this,count,values,(HEAP *)heap);
}
int SESSION_MENU_ARRAY::Choice() {
    if(cursor==count){ShuffleArray(count,values);cursor=0;}
    return values[cursor++];
}
