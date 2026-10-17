// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef struct { Qword q[5]; } Frame;
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
extern float D_0036BBD8;
struct HistoryOwner { unsigned char prefix[0x160]; Frame *frames; float stamp; int flag; };
void func_0016BDE8(struct HistoryOwner *owner,Frame *a,Frame *b,Frame *c)
{
    owner->frames[-1]=owner->frames[0];
    owner->frames[0]=*a;
    owner->frames[1]=*b;
    owner->frames[2]=*c;
    if(*(int *)((char *)owner->frames-0x24)==0) owner->frames[-1]=*a;
    {
        float x;
        if(owner->flag) x=D_0036BBD8;
        else x=D_0036BB98.t;
        owner->stamp=x;
    }
}
