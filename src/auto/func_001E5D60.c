// Private explicit receiver/input correction; algorithm and profile unchanged.
#include "sequence_activity_api.h"
void func_001E5D60(void *receiver,int identifier) {
    if(func_001E5FC8(receiver)==0) {
        func_0023FE38(receiver,identifier);
        return;
    }
    func_001E5F60(receiver,2)->word=identifier;
}
