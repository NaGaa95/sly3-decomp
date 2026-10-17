// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Target { unsigned char prefix[0x130]; int index; unsigned char gap134[0x132C]; void *back; };
struct Object { unsigned char prefix[0x130]; int index; unsigned char gap134[0x84]; int mode; float stamp; unsigned char gap1C0[0x10]; struct Target *target; };
extern float D_0036BB98;
extern unsigned char D_00475480[];
void func_001F4B00(void *game,int index,void *object);
void func_00215F10(struct Object *object,int mode)
{
    int *slot;
    if(object->mode==mode)
        return;
    if(object->mode==1) {
        if(object->target)
            object->target->back=0;
    }
    slot=&object->mode;
    *slot=mode;
    object->stamp=D_0036BB98;
    switch(mode) {
    case 0:
        if(object->target && object->target->index!=-1)
            func_001F4B00(D_00475480,object->target->index,object);
        break;
    case 1:
        if(object->index!=-1 && object->target) {
            object->target->back=object;
            func_001F4B00(D_00475480,object->index,object->target);
        }
        break;
    }
}
