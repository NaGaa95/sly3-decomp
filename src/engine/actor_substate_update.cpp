// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/state_position_ops.h"
struct ActorSubstateUpdateMatrix { qword row[4]; } __attribute__((aligned(16)));
struct ActorSubstateUpdateMethod {
    short adjustment,unused;
    ActorSubstateUpdateMatrix *(*matrix)(void *);
};
struct ActorSubstateUpdateSpatial {
    char prefix[12]; ActorSubstateUpdateMethod *methods;
};
struct ActorSubstateUpdateSubject {
    char prefix[0x4AC]; ActorSubstateUpdateSpatial *spatial;
};
struct ActorSubstateUpdateChild {
    char prefix[0x138]; int state;
    char before_parameters[0x180-0x13C]; void *first; void *second;
};
struct ActorSubstateUpdateEntry { int kind; void *resource; void *message; };
struct ActorSubstateUpdateControl { char prefix[0x18]; unsigned int flags; };
struct ActorSubstateUpdateOwner {
    char prefix[12]; ActorSubstateUpdateMethod *methods;
    char before_control[0x134-0x10]; ActorSubstateUpdateControl *control;
    char before_animation[0x113C-0x138]; void *animation;
    char before_subject[0x11B4-0x1140]; ActorSubstateUpdateSubject *subject;
    char before_state[0x1520-0x11B8]; int outer_state;
    char before_substate[0x1820-0x1524]; int substate; ActorSubstateUpdateEntry *entry;
    char before_child[0x19A4-0x1828]; ActorSubstateUpdateChild *child;
};
extern "C" {
int func_00138AC8(void *animation);
void func_00277208(void *child,void *first,void *second);
void func_0013F8D0(void *receiver);
void func_001B7268(void *context,int kind,void *resource,void *record,float gain);
unsigned int func_00154798(void *receiver,int kind);
void func_0013F870(void *receiver,int mode);
int func_002503C8(void *receiver,float threshold);
int func_0013F840(void *receiver);
void func_0013F440(void *receiver,int state);
}
static inline ActorSubstateUpdateMatrix *SubstateMatrix(ActorSubstateUpdateSpatial *receiver)
{
    ActorSubstateUpdateMethod *method=&receiver->methods[36];
    return method->matrix((char *)receiver+method->adjustment);
}
static inline int SubstateActionEnabled(ActorSubstateUpdateOwner *receiver)
{
    unsigned int mask=func_00154798(receiver,receiver->entry->kind)|0x10;
    return (receiver->control->flags&mask)!=0;
}
static inline VUXScalarCarrier SubstateSquaredLengthXYZ(qword vector)
{
    qword product,one;
    asm("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\t"
        "vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product),"=&j"(one) : "j"(vector));
    return product;
}
extern "C" void func_0013F568(ActorSubstateUpdateOwner *receiver)
{
    int state;
    for(;;) {
        state=receiver->substate;
        ActorSubstateUpdateChild *child=receiver->child;
        switch(state) {
        case 0:
            if(child && child->state==2) goto commit_child;
            if(func_00138AC8(receiver->animation)) func_0013F440(receiver,1);
            break;
        case 1: case 2:
            if(child->state==2) {
commit_child:
                func_00277208(child,child->first,child->second);
                func_0013F8D0(receiver);
                func_001B7268((char *)receiver+0x320,11,0,0,1.0f);
            } else if(child->state==4 || !SubstateActionEnabled(receiver)) {
                func_0013F870(receiver,1);
            } else if(func_002503C8(receiver,0.1f)) {
                func_0013F440(receiver,2);
            } else if(!func_0013F840(receiver)) {
                func_0013F440(receiver,1);
            } else {
                qword target=SubstateMatrix(receiver->subject->spatial)->row[3];
                qword position=SubstateMatrix((ActorSubstateUpdateSpatial *)receiver)->row[3];
                qword difference=PackedDifference(target,position);
                if(PackedSquareRootX(SubstateSquaredLengthXYZ(difference))<300.0f)
                    func_0013F440(receiver,3);
                else func_0013F440(receiver,1);
            }
            break;
        case 3:
            if(child->state==4) func_0013F870(receiver,4);
            else if(func_002503C8(receiver,0.1f)) func_0013F440(receiver,2);
            else if(!func_0013F840(receiver)) func_0013F440(receiver,1);
            else if(!SubstateActionEnabled(receiver)) func_0013F440(receiver,4);
            break;
        case 4:
            if(child && child->state==4) func_0013F870(receiver,4);
            else if(!receiver->animation || func_00138AC8(receiver->animation))
                func_001B7268((char *)receiver+0x320,11,0,0,1.0f);
            break;
        }
        if(receiver->substate==state || receiver->outer_state!=8) break;
    }
}
