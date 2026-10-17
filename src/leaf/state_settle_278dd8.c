// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Object { unsigned char prefix[0x40]; int state; float stamp; };
extern float D_0036BB98;
void func_001C8168(struct Object *object);
void func_00278E58(struct Object *object, int mode);
void func_00278DD8(struct Object *object)
{
    int state;
    func_001C8168(object);
    do {
        state=object->state;
        if(state==1 && 180.0f<D_0036BB98-object->stamp)
            func_00278E58(object,0);
    } while(state!=object->state);
}
