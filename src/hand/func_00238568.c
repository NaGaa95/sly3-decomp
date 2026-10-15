// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
#include "owned_record_list_api.h"
void func_00238568(void *receiver) {
    struct ActorOwnedRecordList *p = (struct ActorOwnedRecordList *)receiver;
    void *retained;
    if (p->count > 0) {
        retained = p->retained;
        func_00238AE8(&retained);
    }
    p->count = 0;
}
