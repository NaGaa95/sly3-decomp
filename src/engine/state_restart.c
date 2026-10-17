// SLY3_CFLAGS: -Os -G0
int func_001BADF8(void *owner,float value,void *record);
void func_00160960(void *self,int mode,int flag);
struct RestartObject { unsigned char prefix[0x10]; void *owner; unsigned char gap14[0x30-0x14]; int kind; float amount; unsigned char gap38[0x74-0x38]; char record[1]; };
void func_00161140(struct RestartObject *object)
{
    if(object->kind!=0xE) {
        if(func_001BADF8(object->owner,object->amount,object->record)) {
            if(object->kind==5) func_00160960(object,-1,0);
            func_00160960(object,5,0);
        }
    }
}
