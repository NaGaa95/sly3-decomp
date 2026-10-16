// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"

struct FrameSubmitView;
struct FrameSubmitGame;
struct DLI;
struct FrameRetirementList { void *first, *last; int link_offset; };
struct FrameRetirementView {
    char prefix[0x34];
    FrameRetirementList objects, particles;
};
struct FrameRetirementParticle {
    char prefix[0x1088];
    void *auxiliary;
};

extern "C" {
extern DLI *D_0036AE94;
extern FrameSubmitGame D_00475480;
int func_0011B0F0(void *list);
void func_0011B028(void *list,void *object);
void func_0011AF40(void *list);
void func_0011E1F0(void *pool,void *allocation);
}

struct FrameRetirementIterator {
    FrameRetirementList *list;
    void **cursor;
    int link_offset;
    DLI *previous;

    FrameRetirementIterator(FrameRetirementList *items)
        : list(items), cursor(reinterpret_cast<void **>(items)),
          link_offset(items->link_offset), previous(D_0036AE94)
    {
        D_0036AE94=reinterpret_cast<DLI *>(this);
    }
    ~FrameRetirementIterator()
    {
        D_0036AE94=previous;
    }
    void *Next()
    {
        void *object=*cursor;
        cursor=reinterpret_cast<void **>(reinterpret_cast<unsigned int>(object)+
                                         static_cast<unsigned int>(link_offset));
        return object;
    }
};

extern "C" void func_001834F8(FrameSubmitView *frame)
{
    FrameRetirementView *view=reinterpret_cast<FrameRetirementView *>(frame);
    if (!func_0011B0F0(&view->objects)) {
        FrameRetirementIterator iterator(&view->objects);
        void *object;
        while ((object=iterator.Next())!=0) {
            func_0011B028(&view->objects,object);
            CallScene(static_cast<SCENE_OBJECT *>(object),2);
        }
        func_0011AF40(&view->objects);
    }
    if (!func_0011B0F0(&view->particles)) {
        FrameRetirementIterator iterator(&view->particles);
        void *object;
        while ((object=iterator.Next())!=0) {
            FrameRetirementParticle *particle=static_cast<FrameRetirementParticle *>(object);
            if (particle->auxiliary)
                func_0011E1F0(reinterpret_cast<char *>(&D_00475480)+0x4894,particle->auxiliary);
            func_0011B028(&view->particles,object);
            func_0011E1F0(reinterpret_cast<char *>(&D_00475480)+0x487C,object);
        }
        func_0011AF40(&view->particles);
    }
}
