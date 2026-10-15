#ifndef SLY3_PRIVATE_INPUT_TABLE_H
#define SLY3_PRIVATE_INPUT_TABLE_H
#include "input_state_more.h"
// These overlapping views expose only proven accesses. In particular, the
// byte lookup view and the callback state view do not assign independent
// storage ownership to their overlapping bytes.
struct INPUT_TABLE_ANALOG_VIEW {
    INPUT_STATE_BASE_VIEW base;
    char prefix30[0x1054-0x30];
    int inputVersion1054;
    char prefix1058[0x1118-0x1058];
    unsigned char values1118[16];
};
struct INPUT_TABLE_BINDING;
struct INPUT_TABLE_GATE_VIEW {
    char prefix1148[0x1148];
    INPUT_TABLE_BINDING *first1148[7];
    INPUT_TABLE_BINDING *second1164[7];
};
struct INPUT_TABLE_REF {
    short kind,padding;
    union { int integer;float scalar;void *pointer; } value;
    INPUT_TABLE_REF(const INPUT_TABLE_REF &);
    ~INPUT_TABLE_REF();
};
extern "C" INPUT_TABLE_REF func_002BC010(const INPUT_TABLE_BINDING *,void *);
extern "C" void func_0012BC20(INPUT_TABLE_REF *);
inline INPUT_TABLE_REF::~INPUT_TABLE_REF() { func_0012BC20(this); }
extern "C" unsigned char D_00468D30[];
struct INPUT_TABLE_CALLBACK_STATE;
struct INPUT_TABLE_CALLBACK_DESCRIPTOR;
struct INPUT_TABLE_CALLBACK_VIEW {
    char prefix1050[0x1050];
    int mode1050,inputVersion1054;
    char prefix1058[0x1124-0x1058];
    // The state starts here; its internal accesses belong to210C08.
    unsigned char callback1124[0x24];
};
extern "C" void func_00210C08(float,INPUT_TABLE_CALLBACK_STATE *,const INPUT_TABLE_CALLBACK_DESCRIPTOR *);
#endif
