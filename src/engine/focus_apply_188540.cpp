// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusLink { unsigned char prefix[0xF0]; int first; int second; };
struct FocusObject { unsigned char prefix[0x6C]; FocusLink *link; unsigned char gap70[0xFC - 0x70]; int first; int second; };
struct FocusGame { unsigned char prefix[0x4048]; FocusObject *object; };
struct FocusSource { unsigned char prefix[0xFC]; int first; int second; };
class FocusGuard {
public:
    FocusLink *link;
    FocusObject *object;
    int linkFirst, objectFirst, linkSecond, objectSecond;
    FocusGuard(FocusObject *target, int first, int second)
    {
        link = target->link;
        object = target;
        objectFirst = object->first;
        object->first = first;
        objectSecond = object->second;
        object->second = second;
        if(link) {
            linkFirst = link->first;
            link->first = first;
            linkSecond = link->second;
            link->second = second;
        }
    }
    ~FocusGuard()
    {
        if(link) {
            link->first = linkFirst;
            link->second = linkSecond;
        }
        if(object) {
            object->first = objectFirst;
            object->second = objectSecond;
        }
    }
};
extern "C" {
extern FocusGame D_00475480;
int func_00188A20(void *self);
void func_00188620(FocusObject *object);
void func_00188658(void *self);
}
extern "C" void func_00188540(FocusSource *self)
{
    if(func_00188A20(self)) return;
    if(D_00475480.object) {
        FocusGuard guard(D_00475480.object, self->first, self->second);
        func_00188620(D_00475480.object);
    }
    func_00188658(self);
}
