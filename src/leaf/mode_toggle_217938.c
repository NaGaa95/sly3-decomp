// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Mode { unsigned char prefix[0x260]; int mode; float stamp; };
extern float D_0036BB98;
int func_0011E8F0(int low,int high);
void func_00217938(struct Mode *m)
{
    switch(m->mode) {
    case 0: m->mode=1; break;
    case 1: m->mode=0; break;
    default: m->mode=func_0011E8F0(0,1); break;
    }
    m->stamp=D_0036BB98;
}
