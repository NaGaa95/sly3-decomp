// Derived scene initialization and callback-driven mode transitions.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene_mode.h"
#include "resource_attachment_api.h"
extern "C" void func_001F3B50(SCENE_MODE_OBJECT *);
extern "C" void func_001F3BF8(SCENE_MODE_OBJECT *);
extern "C" void func_001F3C48(SCENE_MODE_OBJECT *);
extern "C" void func_001CB008(SCENE_MODE_OBJECT *);
extern "C" void func_001CAF70(SCENE_MODE_OBJECT *,int,int,int);
extern "C" void func_001C8970(SCENE_OBJECT *,int,const SCENE_MODE_FIELD *,SCENE_OBJECT *);
extern "C" const SCENE_MODE_FIELD D_00345860[];
extern "C" qword D_00317560;
// Actual integer mode and opaque task pointer use the shared attachment API.
extern "C" void func_0023AAE8(void *,void *,int,int,void **);
extern "C" void func_001CAC30(SCENE_MODE_OBJECT *,int);
extern "C" void func_001CAB30(SCENE_MODE_OBJECT *);
extern "C" void func_00239FE0(void *,int);
extern "C" int func_00226190(void *);
#include "input_query_api.h"
extern "C" int func_001CAFC8(SCENE_MODE_OBJECT *);
extern "C" void func_001C9F00(SCENE_MODE_OBJECT *);
extern "C" unsigned char D_00475480[];
extern "C" void func_001F4B00(void *,int,SCENE_OBJECT *);
extern "C" float D_0036BB98;

extern "C" void func_001C9BF0(SCENE_MODE_OBJECT *object) {
    func_001F3B50(object);
    object->state1B4=-1;
    object->phase1C4=-1;
    object->state1E0=-1;
    object->active1D0=1;
    object->time1D4=3.4028234663852886e38f;
    func_001CB008(object);
    func_001CAF70(object,0x55,0x14,0x4B);
}
extern "C" void func_001C9C58(SCENE_MODE_OBJECT *object) {
    func_001F3BF8(object);
    func_001C8970(&object->scene,9,D_00345860,0);
    object->rotation220=*object->record190->rotation;
    object->result250=func_00130078(object->record194,object->record194->rotation,0,8,2,D_00317560);
    func_0023AAE8(object->observer198,object,-1,0,&object->token1C0);
    func_0023AAE8(object->event258,object->owner254,0x753,0,&object->token25C);
}
extern "C" void func_001C9D10(SCENE_MODE_OBJECT *object) {
    func_001F3C48(object);
    func_001CAC30(object,-1);
    func_001CAC30(object,0);
    object->active1D0=1;
    object->time1D4=3.4028234663852886e38f;
    if(object->token25C)func_00239FE0(object->token25C,0x753);
}
extern "C" void func_001C9D70(SCENE_MODE_OBJECT *object) {
    int previous;
    do {
        previous=object->state1B4;
        switch(previous) {
        case 1:
            if(!object->transition1BC||!func_00226190(object->transition1BC))func_001CAC30(object,3);
            break;
        case 3:
            if(object->active1D0&&func_001A7A80(object->input134,16,0.0f))func_001CAC30(object,2);
            else if((!object->phase1C4||D_0036BB98-object->time1D4>0.4f)&&func_001CAFC8(object))func_001CAC30(object,4);
            else func_001C9F00(object);
            break;
        case 2:
            if(!object->transition1BC||!func_00226190(object->transition1BC))func_001F4B00(D_00475480,object->index130,object->selected1F0);
            break;
        case 4:
            if(!object->transition1BC||!func_00226190(object->transition1BC))func_001F4B00(D_00475480,object->index130,object->selected1F0);
            break;
        case 0:case 5:break;
        }
    } while(object->state1B4!=previous);
}
extern "C" void func_001CA030(SCENE_MODE_OBJECT *object,int enabled) {
    if(object->unknown1C8!=enabled) {
        object->unknown1C8=enabled;
        object->time1D4=enabled?D_0036BB98:3.4028234663852886e38f;
        func_001CAB30(object);
    }
}
