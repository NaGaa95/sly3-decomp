// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
#include "common.h"
struct ActorMatrix { qword row[4]; };
struct Path { SCENE_OBJECT scene; unsigned char gap[0x17C-sizeof(SCENE_OBJECT)]; float end; qword start; qword finish; };
extern "C" void func_00118558(float limit,float time,float scale,qword first,qword second,qword third,qword fourth,qword *outputA,qword *outputB,int flag);
extern "C" void func_00233280(Path *path,qword *startOutput,qword *finishOutput,float time)
{
    if(path->end<=time) {
        if(startOutput)
            *startOutput=path->start;
        if(finishOutput)
            *finishOutput=path->finish;
    } else {
        SCENE_VIRTUAL_ENTRY *entry=&path->scene.vtable[36];
        qword position=((ActorMatrix *(*)(void *))entry->Simple)((char *)path+entry->delta)->row[3];
        entry=&path->scene.vtable[38];
        qword direction=((qword (*)(void *))entry->Simple)((char *)path+entry->delta);
        func_00118558(path->end,time,1.0f,position,direction,path->start,path->finish,startOutput,finishOutput,0);
    }
}
