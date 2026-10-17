// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct FocusLink { unsigned char prefix[0xF0]; int first; int second; };
struct FocusObject { unsigned char prefix[0x6C]; FocusLink *link; unsigned char gap70[0xFC - 0x70]; int first; int second; };
struct FocusNode { unsigned char prefix[0x60]; int active; unsigned char gap64[0x78 - 0x64]; FocusNode *next; };
struct FocusSelf { unsigned char prefix[0x1498]; int firstId; int secondId; };
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
    FocusGuard(FocusLink *target, int first, int second)
    {
        link = target;
        object = 0;
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
extern unsigned char D_004BC230[];
extern unsigned char D_00475480[];
extern unsigned char D_0036C6E8[];
extern unsigned char D_0036C6F0[];
extern FocusNode *D_004794B8;
void func_00283A50(void *table);
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void func_0018A900(int *count, FocusObject ***list);
void func_00188CB0(FocusObject *object);
FocusObject *func_0017E1B8(void *game, int kind, int id, int flag);
void func_00186248(FocusLink *link);
void func_00188540(FocusObject *object);
void func_00189160(void *table, int flag);
void func_00189180(void *table);
int func_00188A20(void *node);
void func_001890B0(FocusObject *object, int kind, int flag);
int func_0011B0F0(void *table);
void func_00188DE0(FocusObject *object);
void func_00188420(FocusObject *object);
}
extern "C" void func_00184B60(FocusSelf *self)
{
    unsigned char frame[16];
    int count;
    FocusObject **list;
    int i;
    FocusObject *first;
    FocusObject *second;
    FocusObject *best;
    FocusNode *node;
    func_00283A50(D_004BC230);
    i = 0;
    func_001D2770(frame);
    func_0018A900(&count, &list);
    for(i = 0; i < count; i++) {
        FocusObject *object = list[i];
        FocusGuard guard(object, 1, 0);
        func_00188CB0(object);
    }
    first = func_0017E1B8(D_00475480, 0x105, self->firstId, 0);
    second = func_0017E1B8(D_00475480, 0x105, self->secondId, 0);
    self->firstId = -1;
    self->secondId = -1;
    if(first) {
        FocusGuard guard((FocusLink *)first, 1, 0);
        func_00186248((FocusLink *)first);
    }
    if(second) {
        FocusGuard guard(second, 1, 0);
        func_00188540(second);
    }
    do {
        func_00189160(D_0036C6E8, 1);
        func_00189180(D_0036C6E8);
        best = 0;
        for(node = D_004794B8; node; node = node->next) {
            if(node->active) {
                if(!func_00188A20(node)) best = (FocusObject *)node;
            }
        }
        if(best) {
            FocusGuard guard(best, 1, 0);
            func_00189160(D_0036C6E8, 0);
            func_001890B0(best, 4, 0);
        }
    } while(!func_0011B0F0(D_0036C6F0));
    for(i = 0; i < count; i++) {
        FocusObject *object = list[i];
        FocusGuard guard(object, 0, 0);
        func_00188DE0(object);
    }
    for(i = 0; i < count; i++) {
        FocusObject *object = list[i];
        FocusGuard guard(object, 1, 0);
        func_00188420(object);
    }
    func_001D2798(frame, 2);
}
