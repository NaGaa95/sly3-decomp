// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
extern "C" DLI *D_0036AE94;
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list)
        : pdl(list), ppv((void **)list), ibDle(list->ibDle),
          pdliNext(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~DLI()
    {
        D_0036AE94 = pdliNext;
    }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};
struct Machine { unsigned char prefix[0x480C]; DL objects; };
extern "C" {
void func_00203078(void *object);
int func_0017E208(Machine *machine, int a, int b, int c, int d, SCENE_OBJECT **found);
}
extern "C" void func_0025BBD0(Machine *machine)
{
    DLI iterator(&machine->objects);
    SCENE_OBJECT *first[0x200];
    SCENE_OBJECT *second[0x200];
    void *object;
    int count, i;
    while((object = iterator.Next()) != 0)
        func_00203078(object);
    count = func_0017E208(machine, 0x405, 0x63, 0, 0x200, first);
    for(i = 0; i < count; i++)
        CallScene(first[i], 9);
    count = func_0017E208(machine, 0x405, 0x1A, 0, 0x200, second);
    for(i = 0; i < count; i++)
        CallScene(second[i], 9);
}
