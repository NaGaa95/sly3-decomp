#include "card_commands.h"
// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
int func_001CEA80(int request);
int func_002A2A48(int n, int *a, int *b);
int func_001CEAA0(int n);
int func_001CEAF0(int command, int result);
int func_001CEFC8(void *unusedContext, int request, int command, int *result) {
    int buf[2];
    int r = func_001CEA80(request);
    if (r != 0x1D) return r;
    r = func_001CEAA0(func_002A2A48(0, &buf[0], &buf[1]));
    if (result) *result = buf[1];
    if (r == 0x22) r = func_001CEAF0(command, buf[1]);
    return r;
}
