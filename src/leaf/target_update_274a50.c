// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Target { unsigned char prefix[0x108]; void *handle; };
struct Updater { unsigned char prefix[0x20]; struct Target *target; void *reference; unsigned char gap28[0xA0]; float gain; };
void func_00273AB0(void *reference,const void *source,qword *output,int flag);
void func_0022EEA0(void *handle,qword position,float gain,int a,int b,int c,int d,float *gainSlot);
void func_00274A50(struct Updater *updater,const void *source)
{
    struct Target *target=updater->target;
    if(target&&target->handle) {
        qword position;
        func_00273AB0(updater->reference,source,&position,0);
        func_0022EEA0(target->handle,position,updater->gain,0,0,0,0,&updater->gain);
    }
}
