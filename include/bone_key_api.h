#ifndef SLY3_BONE_KEY_API_H
#define SLY3_BONE_KEY_API_H
struct BoneKey;
struct BoneBindings;
struct BoneBinding;
struct BoneQueryOwner;
struct BoneResult;
#ifdef __cplusplus
extern "C" {
#endif
void func_00136E28(void *owner,void *context,struct BoneKey *key,
    struct BoneQueryOwner **result_owner,struct BoneResult **result_bone);
struct BoneBinding *func_00136EE0(struct BoneBindings *bindings,
    struct BoneQueryOwner *owner,int required_word94,int require_flag);
#ifdef __cplusplus
}
#endif
#endif
