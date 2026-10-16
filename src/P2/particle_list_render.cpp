// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct RenderMatrix {
    unsigned int words[16];
} __attribute__((aligned(16)));

struct RenderList {
    void *head;
    void *tail;
    int linkOffset;
};
struct RenderIterator {
    RenderList *list;
    void **cursor;
    int linkOffset;
    RenderIterator *previous;
};
struct ChildRenderOps {
    char otherEntries[40];
    short adjustment;
    short reserved;
    void (*render)(void *,int,RenderMatrix *);
};
struct RenderChild {
    char unaccessed[0x14];
    float startTime;
    char unaccessed18[0xE8-0x18];
    ChildRenderOps *operations;
};
struct RenderProperty {
    char unaccessed[0x50];
    RenderList children;
};
extern "C" {
extern RenderIterator *D_0036AE94;
extern float D_0036BB98;
}

static inline void BeginRenderIterator(RenderIterator *iterator,RenderList *list)
{
    iterator->list=list;
    iterator->cursor=(void **)list;
    iterator->linkOffset=list->linkOffset;
    iterator->previous=D_0036AE94;
    D_0036AE94=iterator;
}

static inline void *NextRenderChild(RenderIterator *iterator)
{
    void *child=*iterator->cursor;
    iterator->cursor=(void **)((unsigned int)child+(unsigned int)iterator->linkOffset);
    return child;
}

extern "C" void func_002027F0(RenderProperty *property,int matrixCount,
                              RenderMatrix *matrices)
{
    RenderIterator iterator;
    RenderChild *child;
    BeginRenderIterator(&iterator,&property->children);
    while((child=(RenderChild *)NextRenderChild(&iterator))!=0) {
        if(child->startTime<=D_0036BB98) {
            ChildRenderOps *operations=child->operations;
            operations->render((char *)child+operations->adjustment,
                               matrixCount,matrices);
        }
    }
    D_0036AE94=iterator.previous;
}
