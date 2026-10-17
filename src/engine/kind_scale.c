// SLY3_CFLAGS: -Os -G0
struct KindObject { unsigned char prefix[0x30]; int kind; };
float func_00134B98(struct KindObject *object,float amount)
{
    float result;
    if(object->kind==1) result=2.0f;
    else if(object->kind==2) result=amount*14.0f+2.0f;
    else result=0.0f;
    return result;
}
