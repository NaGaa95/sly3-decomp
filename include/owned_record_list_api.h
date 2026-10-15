#ifndef SLY3_OWNED_RECORD_LIST_API_H
#define SLY3_OWNED_RECORD_LIST_API_H
/* Observed twelve-byte prefix: owner pointer, reference count, retained object pointer. */
struct ActorOwnedRecordList { void *owner; int count; void *retained; };
void func_00238568(void *list);
void func_00238AE8(void *retainedReference);
void func_00238770(void *list);
#endif
