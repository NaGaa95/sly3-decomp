// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusLink { unsigned char prefix[0xF0]; int first; int second; };
struct FocusObject { unsigned char prefix[0x6C]; FocusLink *link; unsigned char gap70[0xFC - 0x70]; int first; int second; };
struct FocusSet {
    unsigned char prefix[0x44]; int state; unsigned char gap48[0x90 - 0x48]; int count; FocusObject **list;
    unsigned char gap98[0xFC - 0x98]; int first; int second;
};
class FocusGuard {
public:
    FocusLink *link;
    FocusObject *object;
    int linkFirst, objectFirst, linkSecond, objectSecond;
    FocusGuard(FocusObject *target, int first, int second)
    {
        link = target->link;
        object = target;
        if(object) {
            objectFirst = object->first;
            object->first = first;
            objectSecond = object->second;
            object->second = second;
        }
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
void func_0018A3E8(FocusSet *set, int state);
void func_0018A778(FocusObject *object, int state);
}
extern "C" void func_0018A670(FocusSet *set, int state)
{
    if(set->state == state) return;
    func_0018A3E8(set, state);
    for(int i = 0; i < set->count; i++) {
        FocusObject *object = set->list[i];
        FocusGuard guard(object, set->first, set->second);
        func_0018A778(object, set->state);
    }
}
