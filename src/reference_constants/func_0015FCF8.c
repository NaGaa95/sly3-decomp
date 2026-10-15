// Original USA entry 0x15fcf8; ordinary C reconstruction.
// Only receiver A0 is consumed.15F908(receiver) returns its owner10.object134.1A7A80 explicitly receives threshold F12=0, that object A0 and mask16 A1. Original concrete tables35BB68/35BBA0 and their constructor stores prove slot1 consumes A0/A1 and optionally F12; slot2 consumes receiver and returned mask. Complete1A98B8/1A8FB8/1A98C8/1A9010 evidence is in engine_input_mask_query_contract.json. On a nonzero mask, receiver.state40 selects15FD58(receiver,0or1), which uses exactly those inputs and creates its own downstream values. No dynamic class name is assigned.
// SLY3_CFLAGS: -Os -G0
void *func_0015F908(void *);
#include "input_query_api.h"
void func_0015FD58(void *,int);
void func_0015FCF8(char *p)  {
    if(func_001A7A80(func_0015F908(p),16,0.0f)) {
        if(*(int *)(p+0x40)==1)func_0015FD58(p,0);
        else func_0015FD58(p,1);
    }
}
