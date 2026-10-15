#ifndef SLY3_PRIVATE_ACTOR_RECORD_ARRAY_API_H
#define SLY3_PRIVATE_ACTOR_RECORD_ARRAY_API_H
//147E08 traverses count records at byte stride, reading real pointers at+4.
// It creates type83, stores thatpointer in *output and has no integerreturn.
// The optional arrays have outputCount scalar entries and are copied internally.
void func_00147E08(void *actor,int stride,int count,void *records,
    int outputCount,const int *identifiers,const int *counts,void **output);
void func_001B0C70(void *actor,void *records,void **output);
#endif
