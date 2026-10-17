// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusLink { unsigned char prefix[0x18]; int word18; unsigned char gap1C[0xF0 - 0x1C]; int first; int second; };
struct FocusObject { unsigned char prefix[0x6C]; FocusLink *link; unsigned char gap70[0xFC - 0x70]; int first; int second; };
struct FocusSet {
    unsigned char prefix[0x18]; int word18; unsigned char gap1C[0x6C - 0x1C]; FocusLink *link; unsigned char gap70[0xA8 - 0x70]; int slot;
    unsigned char gapAC[4]; int values[2]; unsigned char gapB8[0xFC - 0xB8]; int first; int second;
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
struct FocusTable { unsigned char prefix[0x1498]; int linkWord; int selfWord; };
struct FocusGame { unsigned char prefix[0x438C]; int slot; };
extern "C" {
extern FocusGame D_00475480;
extern FocusTable D_0036C700;
void func_0018AAE0(void *game, void *set);
void func_001854C8(void *table, int kind, void *link);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void func_0018A900(int *count, FocusObject ***list);
void func_00188CB0(FocusObject *object);
void func_00189B08(void *set, int flag);
void func_0018A3E8(FocusObject *object, int state);
void func_001856E0(void *table, int index, int value);
}
extern "C" void func_0018A0D0(FocusSet *set)
{
    unsigned char frame[16];
    int count;
    FocusObject **list;
    int i;
    func_0018AAE0(&D_00475480, set);
    func_001854C8(&D_0036C700, 0x22, set->link);
    i = 0;
    func_001D2770(frame);
    func_0018A900(&count, &list);
    for(i = 0; i < count; i++) {
        FocusObject *object = list[i];
        FocusGuard guard(object, 3, 0);
        func_00188CB0(object);
    }
    {
        FocusGuard guard((FocusObject *)set, 3, 0);
        func_00189B08(set, 1);
    }
    for(i = 0; i < count; i++) {
        FocusObject *object = list[i];
        FocusGuard guard(object, 2, 0);
        func_0018A3E8(object, -1);
    }
    D_0036C700.linkWord = set->link->word18;
    D_0036C700.selfWord = set->word18;
    if(set->slot != -1) D_00475480.slot = set->slot;
    else D_00475480.slot = 0x1A8;
    for(i = 0; i < 2; i++) func_001856E0(&D_0036C700, i, set->values[i]);
    func_001D2798(frame, 2);
}
