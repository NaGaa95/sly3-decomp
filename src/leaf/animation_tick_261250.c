// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct Transform { int words[8]; } __attribute__((aligned(16)));
struct Pose { Qword row[4]; };
struct VirtualEntry { short delta,unused; void *function; };
struct FollowObject { char prefix[0xC]; struct VirtualEntry *methods; };
struct Context;
struct Game;
struct Animation {
    char prefix[0x48];
    int state;
    float started;
    int tick,mode;
    float updated;
    int unused5C;
    int first,second,third,selected,unused70;
    void *sprite;
    float animationTime,duration;
    char gap80[0x64];
    struct FollowObject *follow;
    struct Context *context;
    struct Transform *transform;
};
struct Clock { char prefix[0x40]; float time,delta; };
extern struct Clock D_0036BB98;
extern struct Transform D_00317FC0;
extern struct Game D_00475480;
void func_001C8168(void *);
int func_00260758(struct Animation *,int);
void func_00261050(struct Animation *,int);
void func_00261070(struct Animation *,int);
struct Context *func_00165B28(struct Game *);
Qword func_001678C8(struct Context *,Qword);
void func_002625D8(struct Animation *,struct Context *,Qword);
void func_002675C0(void *,struct Transform *,float);
void func_00261250(struct Animation *self)
{
    int state;
    func_001C8168(self);
    state=self->state;
    if(state==1) {
        if(self->mode==2)
            state=self->second==-1?2:3;
    } else if(self->updated!=D_0036BB98.time) {
        switch(state) {
        case 2:
            if(!func_00260758(self,self->selected))
                func_00261050(self,1);
            if(self->duration>0.0f&&self->duration<D_0036BB98.time-self->started)
                func_00261050(self,1);
            if(self->mode==1)
                state=self->third==-1?1:4;
            break;
        case 3:
            if(!func_00260758(self,self->second)) {
                switch(self->mode) {
                case 1: state=self->third==-1?1:4; break;
                case 2: state=2; break;
                }
            }
            break;
        case 4:
            if(!func_00260758(self,self->third)) {
                switch(self->mode) {
                case 1: state=1; break;
                case 2: state=self->second==-1?2:3; break;
                }
            }
            break;
        }
    }
    func_00261070(self,state);
    if(self->selected!=-1) {
        float delta=D_0036BB98.delta;
        struct Transform *transform;
        self->animationTime+=delta;
        if(self->follow) {
            struct Context *context=self->context;
            struct VirtualEntry *method;
            struct Pose *pose;
            Qword point;
            if(!context)
                context=func_00165B28(&D_00475480);
            method=&self->follow->methods[36];
            pose=((struct Pose *(*)(void *))method->function)
                ((char *)self->follow+method->delta);
            point=func_001678C8(context,pose->row[3]);
            func_002625D8(self,context,point);
        }
        transform=self->transform;
        if(!transform)
            transform=&D_00317FC0;
        func_002675C0(self->sprite,transform,delta);
    }
}
