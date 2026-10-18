// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
union MovementVector { qword packed;float component[4]; };
struct MovementMatrix { MovementVector row[3]; };
struct MovementMethod { short adjustment,padding;void *function; };
struct MovementInput {
    char prefix[8];float strength;char before_flags[0x18-0xC];unsigned int flags;
    char before_methods[0x2C-0x1C];MovementMethod *methods;
};
struct MovementAnimation { char prefix[0x40];float rate; };
struct MovementAxis { float weight;int active;char prefix[8];MovementVector direction; };
struct MovementOwner {
    char prefix[12];MovementMethod *methods;
    char before_input[0x134-0x10];MovementInput *input;
    char before_acceleration[0x1A0-0x138];MovementVector acceleration;
    char before_orientation[0x1C0-0x1B0];MovementMatrix orientation;
    char before_controller[0x320-0x1F0];char controller[0x500-0x320];
    char context[0xF60-0x500];char request[0x110C-0xF60];float heading;
    char before_animation[0x113C-0x1110];MovementAnimation *animation;
    char before_side[4];int side;char before_target[0x11B4-0x1148];void *target;
    char before_blocked[0x13E8-0x11B8];int blocked;
    char before_state[0x1520-0x13EC];int state;float state_time;
    char before_axes[0x1770-0x1528];MovementAxis axes[8];void *motion_request;int movement;
};
extern "C" {
extern float D_0036BB98;
int func_00153290(MovementOwner *,int);
void func_001DE690(MovementOwner *,int);
int func_00156998(MovementOwner *);
void func_001DE398(MovementOwner *,int);
int func_001A7A80(MovementInput *,int,float);
void func_001B7268(void *,int,void *,void *,float);
int func_001DF888(MovementOwner *);
int func_001B5170(void *);
int func_001E0DF8(MovementOwner *);
void func_001E0E58(MovementOwner *);
void func_001BDA88(void *,int,void *);
void func_001E0F38(MovementOwner *);
void func_0024E920(MovementOwner *,void *);
qword func_0011FD70(float,float,float);
void func_001C1550(MovementOwner *,MovementAxis *,void *);
}
static inline float MovementHorizontalLength(qword vector) {
    VUXScalarCarrier scalar;
    asm("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y"
        : "=j"(scalar) : "j"(vector));
    asm("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(scalar));
    return PackedVectorX(scalar);
}
static inline qword MovementToVU(qword value) {
    qword result;
    asm("qmtc2.ni %1,%0" : "=j"(result) : "r"(value));
    return result;
}
static inline qword MovementLoad(const MovementVector *value) {
    qword result;
    asm("lqc2 %0,%1" : "=j"(result) : "m"(*value));
    return result;
}
static inline qword MovementTransposeDirection(const MovementMatrix *matrix,qword vector) {
    qword result=MovementLoad(&matrix->row[0]);
    qword second=matrix->row[1].packed,third=matrix->row[2].packed;
    qword one,x,y,z;
    asm("vmul.xyzw %2,%0,%7\n\tvmaxw.xyzw %1,$vf0,$vf0w\n\t"
        "vmul.xyzw %3,%5,%7\n\tvmul.xyzw %4,%6,%7\n\t"
        "vadday.x $ACC,%2,%2y\n\tvmaddz.x %0,%1,%2z\n\t"
        "vaddax.y $ACC,%3,%3x\n\tvmaddz.y %0,%1,%3z\n\t"
        "vaddax.z $ACC,%4,%4x\n\tvmaddy.z %0,%1,%4y"
        : "+j"(result),"=&j"(one),"=&j"(x),"=&j"(y),"=&j"(z)
        : "j"(second),"j"(third),"j"(vector));
    return result;
}
extern "C" void func_001DDFE8(MovementOwner *owner) {
    int before;
    for(;;) {
        before=owner->movement;
        switch(before) {
        case 0: case 1:
            if((owner->input->flags&8) || owner->blocked || !func_00153290(owner,1))
                func_001DE690(owner,0);
            else if(func_00156998(owner)) func_001DE398(owner,0);
            else if(func_001A7A80(owner->input,0x40,0.1f))
                func_001B7268(owner->controller,1,0,0,1.0f);
            else if(func_001DF888(owner)) {}
            else if(func_001A7A80(owner->input,0x20,0.2f) && func_001B5170(owner->context)) {}
            else if(func_001E0DF8(owner) && func_001A7A80(owner->input,0x80,0.15f))
                func_001E0E58(owner);
            else if(((int (*)(void *,int,float))owner->input->methods[1].function)
                        ((char *)owner->input+owner->input->methods[1].adjustment,0x400,0.15f)
                    && 0.1f<D_0036BB98-owner->state_time
                    && ((int (*)(void *,int))owner->methods[113].function)
                        ((char *)owner+owner->methods[113].adjustment,3)) {
                func_001DE398(owner,0);
                ((void (*)(void *,int))owner->input->methods[2].function)
                    ((char *)owner->input+owner->input->methods[2].adjustment,0x400);
                func_001BDA88(owner->request,0,0);
            } else if(func_001E0DF8(owner) && func_001A7A80(owner->input,0x10,0.15f))
                func_001E0F38(owner);
            else {
                float strength=owner->input->strength;
                if(owner->state==0?0.1f<strength:0.0f<strength) func_001DE398(owner,1);
                else func_001DE398(owner,0);
            }
            break;
        }
        if(owner->movement==before || owner->state!=10) break;
    }
    switch(owner->movement) {
    case 0:
        func_0024E920(owner,owner->target);
        break;
    case 1: {
        func_0024E920(owner,owner->target);
        float length=MovementHorizontalLength(owner->axes[1].direction.packed);
        MovementInput *input=owner->input;
        qword direction=MovementToVU(func_0011FD70(owner->heading+3.1415927f,
                                (input->strength*length)*owner->animation->rate,0.0f));
        owner->acceleration.packed=direction;
        qword world=MovementTransposeDirection(&owner->orientation,direction);
        owner->side=-1;
        owner->acceleration.packed=world;
        func_001C1550(owner,owner->axes,owner->motion_request);
        break;
    }
    }
}
