// SLY3_CFLAGS: -Os -G0
#include "matrix_xy_resource_api.h"
struct Pair { float first; float second; unsigned char gap[8]; };
struct Object { unsigned char prefix[0x94]; int state; unsigned char gap98[0x98]; int enabled; int index; };
extern struct Pair D_00325E80[];
extern int D_00325EA0[];
void *func_00292034(void *destination,int value,int bytes);
void func_0021BC58(struct Object *object)
{
    struct MatrixXYValue matrix;
    if((unsigned int)(object->state-8)<2) {
        if(!object->enabled || object->index==-1) {
            func_00292034(&matrix,0,sizeof(matrix));
            matrix.value[3]=1.0f;
            matrix.value[0]=1.0f;
        } else {
            func_00292034(&matrix,0,sizeof(matrix));
            {
                struct Pair *pair=&D_00325E80[object->index];
                matrix.value[0]=1.0f;
                matrix.value[3]=1.0f;
                matrix.value[4]=pair->first;
                matrix.value[5]=pair->second;
            }
        }
        if(object->index==-1)
            object->state=8;
        else
            object->state=D_00325EA0[object->index];
        func_00262848(object,&matrix);
    }
}
