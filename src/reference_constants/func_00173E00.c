// SLY3_CFLAGS: -Os -G0
#include "position_attachment_api.h"
struct PositionContext {
    char pad[0x47A8];
    void *space0;
    void *space1;
};
void *func_00173E00(void *context,int kind,SequencePackedPosition position,int attachmentWord) {
    struct PositionContext *p=context;
    void *space;
    switch(kind) {
        case 0:space=p->space0;
        break;
        case 1:space=p->space1;
        break;
    }
    return func_001738C0(space,position,attachmentWord);
}
