// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_lifecycle_api.h"

struct ParticleList { void *head, *tail; int link_offset; };
struct ParticleIterator;
extern "C" {
extern ParticleIterator *D_0036AE94;
extern float D_0036BB9C;
int func_00203170(void *owner);
void func_00203078(void *owner);
int func_0011B0F0(int *head_word);
}
struct ParticleIterator {
    ParticleList *list;
    void **cursor;
    int link_offset;
    ParticleIterator *previous;
    ParticleIterator(ParticleList *value)
        : list(value), cursor((void **)value), link_offset(value->link_offset),
          previous(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~ParticleIterator()
    {
        D_0036AE94 = previous;
    }
    void *Next()
    {
        void *node = *cursor;
        cursor = (void **)((unsigned int)node + (unsigned int)link_offset);
        return node;
    }
};
struct ParticleOwnerUpdateView {
    unsigned char prefix[0x64];
    float elapsed;
    unsigned char reserved68[4];
    ParticleList children;
};

extern "C" void func_00202D80(void *owner)
{
    ParticleOwnerUpdateView *view = (ParticleOwnerUpdateView *)owner;
    view->elapsed += D_0036BB9C;
    ParticleIterator iterator(&view->children);
    int flags = func_00203170(owner);
    void *child;
    while ((child = iterator.Next()) != 0)
        func_001FEF60((Property *)child, flags);
    if (func_0011B0F0((int *)&view->children))
        func_00203078(owner);
}
