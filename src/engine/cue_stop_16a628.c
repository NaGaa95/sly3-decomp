// SLY3_CFLAGS: -Os -G0
struct CueRef { void *object; };
struct CueSelf {
    void *pose;
    unsigned char gap4[0x20-4]; void *target; float x; float y;
    unsigned char gap2C[0x48-0x2C]; struct CueRef first; struct CueRef second;
};
void func_00244CA8(void *sound,float value);
void func_002BBCD8(void *reference,void *value);
int func_0013B500(void *object,int identifier);
void func_00166560(void *pose,float a,float b);
void func_00169E40(void *self);
void func_0016A628(struct CueSelf *self)
{
    struct CueRef *reference=&self->first;
    if(reference && reference->object) {
        func_00244CA8(reference->object,0.0f);
        func_002BBCD8(reference,0);
    }
    reference=&self->second;
    if(reference && reference->object) {
        func_00244CA8(reference->object,0.5f);
        func_002BBCD8(reference,0);
    }
    if(func_0013B500(self->target,0x33)) func_00166560(self->pose,self->x+3.14159274f,-self->y);
    func_00169E40(self);
}
