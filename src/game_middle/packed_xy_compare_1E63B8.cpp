// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"
extern "C" int func_001E63B8(qword left,qword right) {
    float left_x=PackedVectorX(left),right_x=PackedVectorX(right);
    if(left_x<right_x) return -1;
    if(right_x<left_x) return 1;
    float left_y=PackedVectorY(left),right_y=PackedVectorY(right);
    if(left_y<right_y) return -1;
    if(right_y<left_y) return 1;
    return 0;
}
