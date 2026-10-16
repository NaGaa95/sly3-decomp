// SLY3_CFLAGS: -Os -G0
struct ModeObject { char unknown_0[0x1B0]; int flag_a; int unknown_1B4; int flag_b; };
void func_001F4548(void *object,int mode);
void func_002159D8(void *object,int request);
void func_002147B0(struct ModeObject *object,int mode)
{
    func_001F4548(object,mode);
    if(mode==-1) {
        if(object->flag_b!=1 && object->flag_a!=1)
            func_002159D8(object,0);
        return;
    }
    func_002159D8(object,2);
}
