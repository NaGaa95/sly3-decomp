// SLY3_CFLAGS: -Os -G0
struct SeekObject { unsigned char prefix[0x14]; void *library; unsigned char gap18[0x1C-0x18]; float time; unsigned char gap20[0x40-0x20]; float rate; };
struct SeekSelf { unsigned char prefix[4]; int mode; unsigned char gap8[0x18-8]; struct SeekObject *object; };
float *func_00136880(void *library,int key);
void func_00137D08(void *runtime,int seek,float time,float rate,int update_mode);
void func_0013ABC8(void *self,int state);
void func_0013AB30(struct SeekSelf *self)
{
    if(self->mode<2) {
        if(self->mode>=0) {
            float *limit=func_00136880(self->object->library,0x2A8);
            if(!limit) {
                func_0013ABC8(self,-1);
            } else {
                struct SeekObject *object=self->object;
                if(object->time<*limit) func_00137D08(object,0,*limit,object->rate,0);
                func_0013ABC8(self,3);
            }
        }
    }
}
