// Private explicit receiver/input correction; algorithm and profile unchanged.
#include "sequence_activity_api.h"
void func_001E5E48(void *receiver,int identifier) {
    if(func_001E5FC8(receiver)==0) {
        func_0023FEC0(receiver,identifier);
        return;
    }
    func_001E5F60(receiver,3)->word=identifier;
}
