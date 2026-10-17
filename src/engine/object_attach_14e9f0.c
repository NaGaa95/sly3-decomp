// SLY3_CFLAGS: -Os -G0
struct AttachGlobals { unsigned char prefix[0x4E4C]; void *resource; };
extern struct AttachGlobals D_00475480;
int func_001C8658(void *object);
int func_0014ECD0(void *self);
void *func_001FBE30(void *resource,int flag);
void func_0014DBB8(void *object,int value);
void func_0014DC98(void *object,int state);
void func_0014E9F0(char *self)
{
    void *object;
    int value;
    if(func_001C8658(self)) {
        if(!*(void **)(self+0x1A4)) {
            if(D_00475480.resource) {
                value=func_0014ECD0(self);
                if(value!=-1) {
                    object=func_001FBE30(D_00475480.resource,0);
                    *(void **)(self+0x1A4)=object;
                    if(object) {
                        func_0014DBB8(object,value);
                        *(void **)(*(char **)(self+0x1A4)+0x13C)=self;
                        func_0014DC98(*(void **)(self+0x1A4),1);
                    }
                }
            }
        }
    } else {
        if(*(void **)(self+0x1A4)) func_0014DC98(*(void **)(self+0x1A4),0);
    }
}
