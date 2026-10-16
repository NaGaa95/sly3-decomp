// SLY3_CFLAGS: -Os -G0
#include "sequence_activity_api.h"
struct SequenceGateKind { int kind, word; };
struct SequenceSourceGate {
    char prefix[0x130];
    int count;
    struct SequenceGateKind *rows;
};
int func_0013B500(void *object, int kind);

int func_001E4FC8(struct SequenceSourceGate *gate, int mask, void *object)
{
    int i;
    if (func_001E5FF8(gate)) return 0;
    if (!(mask & 2)) return 0;
    if (gate->count != 0 && object != (void *)gate) {
        for (i = 0; i < gate->count; i++) {
            if (func_0013B500(object, gate->rows[i].kind)) break;
        }
        if (i >= gate->count) return 0;
    }
    return 1;
}
