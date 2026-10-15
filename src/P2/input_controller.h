#ifndef SLY3_PRIVATE_INPUT_CONTROLLER_H
#define SLY3_PRIVATE_INPUT_CONTROLLER_H
#include "input_interface.h"
struct INPUT_CONTROLLER_MODE;
struct INPUT_PRIORITY_NODE {
    char prefixD4[0xD4];INPUT_PRIORITY_NODE *nextD4;
    char prefixD8[0x14C-0xD8];int priority14C;
    char prefix150[0x300-0x150];INPUT_CONTROLLER_MODE *mode300;
};
struct INPUT_PRIORITY_LIST { INPUT_PRIORITY_NODE *first,*last;int linkOffset; };
struct INPUT_MODE_RANGE { float minimum,maximum; };
struct INPUT_CONTROLLER : INPUT_INTERFACE {
    char prefix30[0x40-0x30];
    unsigned char buffer40[0x1000];
    int id1040,port1044,slot1048;
    int reset104C,mode1050,version1054;
    float time1058;unsigned int reset105C;
    char prefix1060[8];unsigned int previous1068,active106C;
    float timestamps1070[16];
    char prefix10B0[4];float leftScalar10B4;unsigned int leftReset10B8;
    INPUT_MODE_RANGE leftRanges10BC[4];
    char prefix10DC[4];float rightScalar10E0;unsigned int rightReset10E4;
    INPUT_MODE_RANGE rightRanges10E8[4];
    char prefix1108[16];unsigned char pressure1118[12];
    unsigned char callback1124[0x24];
    void *first1148[7],*second1164[7];
    int reset1180[5];
    INPUT_PRIORITY_LIST list1194;
};
struct INPUT_CONTROLLER_RELATED { char prefix198[0x198];int state198; };
struct INPUT_CONTROLLER_MODE {
    char prefix8[8];int kind8;
    char prefixC[0x20-0xC];INPUT_CONTROLLER_RELATED *related20;
};
struct INPUT_CONTROLLER_RESOLVED { char prefix19C[0x19C];int value19C; };
extern "C" void func_001A8780(INPUT_CONTROLLER *,int,int);
extern "C" int func_002A1680(int,int,void *);
extern "C" void func_0011AF38(INPUT_PRIORITY_LIST *,int);
extern "C" void func_0011AF40(INPUT_PRIORITY_LIST *);
extern "C" void func_0011AFC0(INPUT_PRIORITY_LIST *,INPUT_PRIORITY_NODE *,INPUT_PRIORITY_NODE *);
extern "C" void func_00210A60(void *);
extern "C" void *memset(void *,int,unsigned int);
extern "C" void func_001A7CE0(INPUT_CONTROLLER *);
extern "C" INPUT_PRIORITY_NODE *func_001A91D8(INPUT_CONTROLLER *);
extern "C" INPUT_CONTROLLER_RESOLVED *func_001662A8(INPUT_PRIORITY_NODE *);
#endif
