/* Physical pointer inputs proved by both original RO slot-10 implementations. */
#ifndef SLY3_OWNER_PARENT_LINK_H
#define SLY3_OWNER_PARENT_LINK_H
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*OwnerParentCallback)(void *receiver, void *parent, void *parent_node, int flags);
void func_001C7A00(void *receiver, void *parent, int flags);
#ifdef __cplusplus
}
#endif
#endif
