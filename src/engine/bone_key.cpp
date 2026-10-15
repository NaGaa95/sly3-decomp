// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "bone_key_api.h"
struct BoneKey {
    int object_id : 20;
    int bone_index : 10;
    unsigned int required : 1;
    unsigned int excluded : 1;
};
struct BoneResult { unsigned char prefix[0x94]; int word94; };
struct BoneQueryEntry {
    short adjustment, reserved;
    BoneResult *(*query)(void *,int);
};
struct BoneQueryOwner {
    unsigned char prefix[0xC]; BoneQueryEntry *table;
    unsigned char unaccessed10[8]; int identifier;
};
struct BoneBinding { BoneKey key; void *curve; };
struct BoneBindings {
    unsigned char prefix[0x4C]; int count; BoneBinding *entries;
};
extern "C" {
extern unsigned char D_00475480[];
void *func_0017E1B8(void *,int,int,void *);
}

extern "C" void func_00136E28(void *owner,void *context,BoneKey *key,
    BoneQueryOwner **result_owner,BoneResult **result_bone)
{
    if (context)
        *result_owner = (BoneQueryOwner *)func_0017E1B8(D_00475480,1,key->object_id,context);
    else
        *result_owner = (BoneQueryOwner *)func_0017E1B8(D_00475480,4,key->object_id,owner);
    if (!*result_owner)
        *result_bone = 0;
    else {
        BoneQueryEntry *entry = &(*result_owner)->table[55];
        *result_bone = entry->query((char *)*result_owner+entry->adjustment,key->bone_index);
    }
}

extern "C" BoneBinding *func_00136EE0(BoneBindings *bindings,BoneQueryOwner *owner,
    int required_word94,int require_flag)
{
    for (int index = 0; index < bindings->count; ++index) {
        BoneBinding *entry = &bindings->entries[index];
        if (require_flag && !entry->key.required)
            continue;
        if (entry->key.object_id != owner->identifier)
            continue;
        if (entry->key.excluded)
            continue;
        BoneQueryEntry *query = &owner->table[55];
        if (query->query((char *)owner+query->adjustment,entry->key.bone_index)->word94 == required_word94)
            return entry;
    }
    return 0;
}
