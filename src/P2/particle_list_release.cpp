// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_lifecycle_api.h"
struct ParticleList { void *head, *tail; int link_offset; };
struct ParticleListIterator;
extern "C" {
extern ParticleListIterator *D_0036AE94;
void func_001FF098(Property *);
void func_001495F8(char *);
void func_002BEA28(void *, int);
}
struct ParticleListIterator {
    ParticleList *list;
    void **cursor;
    int link_offset;
    ParticleListIterator *previous;
    ParticleListIterator(ParticleList *value)
        : list(value), cursor((void **)value),
          link_offset(value->link_offset), previous(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~ParticleListIterator()
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
struct ListReleasePropertyView {
    unsigned char prefix[0x50];
    ParticleList children;
};
extern "C" void func_002017E0(void *receiver)
{
    ListReleasePropertyView *p = (ListReleasePropertyView *)receiver;
    func_001FF098((Property *)receiver);
    ParticleListIterator iterator(&p->children);
    void *child;
    while ((child = iterator.Next()) != 0)
        func_001495F8((char *)child);
    if (receiver)
        func_002BEA28(receiver, 3);
}
