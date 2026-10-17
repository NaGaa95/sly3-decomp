// SLY3_CFLAGS: -Os -G0
struct TailSelf { unsigned char prefix[0xB4]; void *first; unsigned char gapB8[0xC0-0xB8]; void *second; };
struct TailObject { unsigned char prefix[0x3C]; unsigned int tagged; };
extern char D_00370AF0[];
extern char D_004BC230[];
int func_001C6F20(void *runtime);
void func_001C6F30(void *runtime);
int func_002852B0(void *context);
void func_00283F70(void *context);
void func_00189078(void *object,int state,void *source);
void func_0027FCC8(void *object);
void func_001874E8(struct TailSelf *self)
{
    struct TailObject *object;
    if(func_001C6F20(D_00370AF0)) {
        func_001C6F30(D_00370AF0);
        return;
    }
    if(func_002852B0(D_004BC230)) {
        func_00283F70(D_004BC230);
        return;
    }
    if(self->first) {
        func_00189078(self->first,4,self);
        return;
    }
    object=self->second;
    if(object) {
        unsigned int v=object->tagged;
        if((v^1)&1) *(unsigned int *)v|=0x200;
        else object->tagged=v|0x200;
        func_0027FCC8(self->second);
    }
}
