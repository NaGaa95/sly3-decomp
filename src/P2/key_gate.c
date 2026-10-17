// SLY3_CFLAGS: -Os -G0
struct KeyEvent { int unknown_0; void *key; };
int func_0013B500(void *key,int kind);
int func_0025CE90(void *owner,struct KeyEvent *event);
int func_00232C58(void *owner,struct KeyEvent *event)
{
    int result=0;
    if(!func_0013B500(event->key,0x7E) && !func_0013B500(event->key,0x31) && !func_0013B500(event->key,0x61))
        result=func_0025CE90(owner,event)!=0;
    return result;
}
