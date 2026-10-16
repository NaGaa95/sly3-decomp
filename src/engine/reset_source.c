// SLY3_CFLAGS: -Os -G0
#include "owner_parent_link.h"
#include "reset_source_link_api.h"
struct ResetSourceObject {
    char prefix[0x134];
    float time;
    char unused138[0x150-0x138];
    unsigned int word150;
    char unused154[0x1C0-0x154];
    unsigned int word1C0;
    char unused1C4[8];
    unsigned int word1CC;
};
extern float D_00320290;
void func_001FC968(void *receiver, void *owner);
void func_0023EBF8(void *receiver, int enabled);
void func_0023EC98(void *receiver, int enabled);
void func_0023FC90(void *receiver, unsigned int enabled);
void func_0014D108(struct ResetSourceObject *object, void *owner)
{
    func_001FC968(object, owner);
    object->word150=0;
    object->time=D_00320290;
    func_0014D1F0(object, object);
    func_0023EBF8(object, 0);
    func_0023EC98(object, 0);
    func_0023FC90(object, 0);
    object->word1CC=0;
    object->word1C0=0;
    func_001C7A00(object, 0, 15);
}
