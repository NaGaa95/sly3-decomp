// Original scene mode callbacks, selections and transition notifications.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene_mode.h"
extern "C" const int D_00323840[3]={132,144,166};
extern "C" const int D_00323850[6]={159,160,161,-1,164,165};
extern "C" void func_00239DB8(void *,int);
extern "C" void func_00226050(void *);
extern "C" void func_001CAD10(SCENE_MODE_OBJECT *,int);
extern "C" void func_001CB008(SCENE_MODE_OBJECT *);
extern "C" void func_0012F4F8(void *,qword);
extern "C" void func_00225EE8(void *,SCENE_OBJECT *);
extern "C" qword D_00317560;
extern "C" float D_0036BB98;
extern "C" void func_00239CE8(void *,int);
extern "C" void func_001CA030(SCENE_MODE_OBJECT *,int);
extern "C" void func_001CAE80(SCENE_MODE_OBJECT *,unsigned int,int);
struct SCENE_MODE_PLAYER { char prefix1124[0x1124];char input1124[0x11C0-0x1124]; };
extern "C" SCENE_MODE_PLAYER D_0036E740[];
extern "C" void func_00210C90(void *,int);

extern "C" void func_001CAB30(SCENE_MODE_OBJECT *object) {
    if(object->token1C0) {
        if(object->state1B4==3) {
            if(object->unknown1C8)func_00239DB8(object->token1C0,0xA3);
            else func_00239DB8(object->token1C0,D_00323840[object->phase1C4]);
        } else func_00239DB8(object->token1C0,D_00323850[object->state1B4]);
    }
}
extern "C" float func_001CABB8(SCENE_MODE_OBJECT *object,int index) {
    float value=1.0f;
    switch(object->modes20C[index]) {
    case 2:case 4:case 6:
        if(index&1)break;
        value=-1.0f;
        break;
    case 1:case 3:case 5:
        if(index&1)value=-1.0f;
        break;
    case -1:case 0:break;
    }
    return value;
}
extern "C" void func_001CAC30(SCENE_MODE_OBJECT *object,int state) {
    if(state!=object->state1B4) {
        if(object->transition1BC) {
            func_00226050(object->transition1BC);
            object->transition1BC=0;
        }
        if(object->state1B4==3)func_001CAD10(object,-1);
        *(&object->state1B4)=state;
        object->time1B8=D_0036BB98;
        if(state==3) {
            func_001CAD10(object,0);
            func_001CB008(object);
            func_0012F4F8(object->result250,D_00317560);
        }
        if(object->state1B4!=-1) {
            object->transition1BC=object->transitions19C[object->state1B4];
            if(object->transition1BC)func_00225EE8(object->transition1BC,object->selected1F0);
            func_001CAB30(object);
        }
    }
}
extern "C" void func_001CAD10(SCENE_MODE_OBJECT *object,int phase) {
    if(phase!=object->phase1C4) {
        SCENE_MODE_PLAYER *player=&D_0036E740[object->index130];
        switch(object->phase1C4) {
        case -1: {
            func_00210C90(player->input1124,5);
            int storage=object->scene.field3C;
            if(!(storage&1))*(int *)storage|=0x200;
            else object->scene.field3C=storage|0x200;
            break;
        }
        case 2:func_001CB008(object);break;
        }
        *(&object->phase1C4)=phase;
        object->time1CC=D_0036BB98;
        switch(phase) {
        case -1: {
            int storage=object->scene.field3C;
            if(!(storage&1))*(int *)storage&=~0x200;
            else object->scene.field3C=storage&~0x200;
            func_00210C90(player->input1124,1);
            if(object->token25C)func_00239CE8(object->token25C,0x753);
            break;
        }
        case 2:
            for(unsigned int index=0;index<3;++index)func_001CAE80(object,index,-1);
            if(object->token25C)func_00239CE8(object->token25C,0x753);
            break;
        }
        func_001CAB30(object);
    }
}
extern "C" void func_001CAE80(SCENE_MODE_OBJECT *object,unsigned int index,int mode) {
    object->modes20C[index]=mode;
    if(object->token25C) {
        if(index<2) {
            switch(mode) {
            case 0:case 5:func_00239CE8(object->token25C,0x755);break;
            case 6:func_00239CE8(object->token25C,0x754);break;
            }
        } else if(mode<7) {
            if(mode>=5)func_00239CE8(object->token25C,0x753);
        }
    }
}
extern "C" void func_001CAF70(SCENE_MODE_OBJECT *object,int first,int second,int third) {
    float a=(float)first,b=(float)second,c=(float)third;
    a=a+a;b=b+b;c=c+c;
    object->angles1E4[0]=a*0.03141593f;
    object->angles1E4[1]=b*0.03141593f;
    object->angles1E4[2]=c*0.03141593f;
}
extern "C" void func_001CB008(SCENE_MODE_OBJECT *object) {
    object->elapsed1FC=object->duration200=object->value204=0.0f;
    func_001CAE80(object,0,0);
    func_001CA030(object,0);
    for(unsigned int index=1;index<3;++index)func_001CAE80(object,index,-1);
}
