// SLY3_CFLAGS: -Os -G0
struct Object { unsigned char prefix[0x1274]; int busy; unsigned char gap1278[0x19E0-0x1278]; int mode; };
extern int D_0036DBE0;
int func_0013B868(void *object);
int func_0021EE68(void *unused,struct Object *object)
{
    int diff;
    if(!object)
        return 0;
    diff=D_0036DBE0^2;
    if(!diff)
        return 0;
    switch(func_0013B868(object)) {
    case 0x34:
        if(object->busy)
            return 0;
        return object->mode!=0x16;
    case 0x35:
    case 0x36:
        return !object->busy;
    default:
        return 0;
    }
}
