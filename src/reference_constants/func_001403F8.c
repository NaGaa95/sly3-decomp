// SLY3_CFLAGS: -Os -G0
#include "actor_command_method_api.h"
void func_001403F8(char *receiver, int command) {
    func_001546B0(receiver, command);
    if (command == 13) *(int *)(receiver + 0x19B8) = 0;
}
