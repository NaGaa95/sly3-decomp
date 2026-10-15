#ifndef SLY3_P2_SHUFFLE_ARRAY_H
#define SLY3_P2_SHUFFLE_ARRAY_H

// Names are provisional; layout and virtual slots are recovered from the original
// initialization, refill, constructor, session calls and complete vtables.
#include "heap.h"

extern "C" int func_0011E8F0(int,int);
template<class T>struct SHUFFLE_ARRAY_FIELDS {
    void *vtable;int count;T *values;int cursor;HEAP *heap;
};
template<class T>static inline void ShuffleArray(int count,T *values) {
    if(count>=3) {
        int last=count-1;
        T previous=values[last];
        for(int i=0;i<count;i++) {
            int other=func_0011E8F0(0,last);
            T value=values[i];values[i]=values[other];values[other]=value;
        }
        if(values[0]==previous) {
            int other=func_0011E8F0(1,last);
            T value=values[0];values[0]=values[other];values[other]=value;
        }
    }
}
class SHUFFLE_CHOICE_BASE {
public:
    SHUFFLE_CHOICE_BASE();
    virtual int Choice()=0;
};
class SESSION_MENU_ARRAY:public SHUFFLE_CHOICE_BASE {
public:
    int count;int *values;int cursor;HEAP *heap;
    SESSION_MENU_ARRAY(int,const int *,void *);
    virtual int Choice();
};

#endif
