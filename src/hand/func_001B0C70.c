#include "actor_record_array_api.h"
void func_001B0C70(void *actor,void *records,void **output) {
    void *result;
    func_00147E08(actor,0xC,3,records,0,0,0,&result);
    if(output)*output=result;
}
