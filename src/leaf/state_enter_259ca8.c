// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int QWORD __attribute__((mode(TI)));
extern QWORD D_00317560;
extern float D_0036BB98;
struct State { void *owner; int state; float stamp; };
void func_00240CB0(void *receiver,int option,void *owner,int flags,int identifier,int active,QWORD first,QWORD second,void *output);
void func_00259CA8(struct State *s,int state)
{
    if(s->state!=state) {
        int *slot=&s->state;
        *slot=state;
        s->stamp=D_0036BB98;
        if(state==2)
            func_00240CB0(s->owner,0,s->owner,0x4000,0,0,D_00317560,D_00317560,0);
    }
}
