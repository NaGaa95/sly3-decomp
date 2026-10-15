// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
int func_00291DF8(const void *left,const void *right,unsigned bytes);
}
struct XYZ { float x,y,z; };
struct XY { float x,y; };
extern "C" bool func_0012B818(const CRef *left,const CRef *right) {
    if(left->tag==right->tag) {
    switch(left->tag) {
    case 19: case 20: case 21: case 22: case 23:
    case 29: case 30: case 31: case 32: case 33:
        return left->payload.integer==right->payload.integer;
    case 24: case 26: case 28: {
        const XYZ *a=(const XYZ *)left->payload.pointer;
        const XYZ *b=(const XYZ *)right->payload.pointer;
        return a->x==b->x && a->y==b->y && a->z==b->z;
    }
    case 25:
        return func_00291DF8(left->payload.pointer,right->payload.pointer,64)==0;
    case 27: {
        const XY *a=(const XY *)left->payload.pointer;
        const XY *b=(const XY *)right->payload.pointer;
        return a->x==b->x && a->y==b->y;
    }
    }
    return true;
    }
    return false;
}
