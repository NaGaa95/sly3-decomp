// SLY3_CFLAGS: -Os -G0 -fno-gcse -fno-cse-skip-blocks
struct Object { unsigned char prefix[0x3C]; int tagged; unsigned char gap40[0xE8]; unsigned long state; };
int func_001C8610(struct Object *object);
void func_00211F90(struct Object *object);
void func_00211F18(struct Object *object);
void func_0023CB08(struct Object *object,int enable)
{
    int value=object->tagged;
    int current=value;
    if((value^1)&1)
        current=*(int *)value;
    if(enable) {
        if(current&8)
            return;
        if((value^1)&1)
            *(int *)value|=8;
        else
            object->tagged=value|8;
        if(object->state&8) {
            if(func_001C8610(object))
                func_00211F90(object);
        }
    } else if(current&8) {
        if((value^1)&1)
            *(int *)value&=~8;
        else
            object->tagged=value&~8;
        func_00211F18(object);
    }
}
