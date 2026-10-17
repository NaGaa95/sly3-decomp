// SLY3_CFLAGS: -Os -G0
struct Pos { float v[4]; } __attribute__((aligned(16)));
void *func_001FBE30(void *resource,int flag);
void func_001C8FB0(void *object,void *receiver);
void func_00212770(void *receiver,void *object);
void func_0014CB98(void *object,float value);
void func_0014D1F0(void *object,void *source);
int func_00145080(char *self,void *resource,int word,struct Pos *position,float value)
{
    struct Pos saved=*position;
    void *object;
    if(*(void **)(self+0x47C)) {
        object=func_001FBE30(resource,0);
        if(object) {
            func_001C8FB0(object,*(void **)(self+0x47C));
            *(int *)(*(char **)(self+0x240)+0x50)=word;
            *(struct Pos *)(*(char **)(self+0x240)+0x40)=saved;
            func_00212770(*(void **)(self+0x240),object);
            func_0014CB98(object,value);
            func_0014D1F0(object,self);
            return 1;
        }
    }
    return 0;
}
