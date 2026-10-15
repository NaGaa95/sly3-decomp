// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
extern "C" {
#include "eval_dispatch_api.h"
#include "matrix_xy_resource_api.h"
CRef *func_0024B2B8(CRef *,int,CRef *,int *,...);
void func_00262708(void *,const MatrixXYSource *);
}
extern "C" CRef *func_0010CDE0(CRef *output,void *receiver,int count,CRef *values)
{
    MatrixXYSource matrix[1];
    CRef temporary;
    int schema[1]={4};
    func_0024B2B8(&temporary,1,values,schema,matrix);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary,0x22);
    func_00262708(receiver,matrix);
    func_0012AF00(output,&temporary);
    func_0012BC20(&temporary);
    return output;
}
