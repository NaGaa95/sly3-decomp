// Controller initialization, reset, priority insertion and state dispatch.
// All structure/class names are provisional accessed-field/interface views.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_controller.h"
extern "C" void func_001A7C68(INPUT_CONTROLLER *input,int id,int port,int slot) {
    input->id1040=id;
    func_001A8780(input,1,0);
    input->port1044=port;
    input->slot1048=slot;
    func_002A1680(port,slot,input->buffer40);
    func_0011AF38(&input->list1194,0xD4);
    func_001A7CE0(input);
}
extern "C" void func_001A7CE0(INPUT_CONTROLLER *input) {
    func_00210A60(input->callback1124);
    input->Consume(0xFFFF);
    memset(input->first1148,0,sizeof(input->first1148));
    memset(input->second1164,0,sizeof(input->second1164));
    input->reset1180[4]=0;
    input->reset1180[3]=0;
    input->reset1180[2]=0;
    input->reset1180[1]=0;
    input->reset1180[0]=0;
    func_0011AF40(&input->list1194);
    memset(input->leftStateTimes1C,0,sizeof(input->leftStateTimes1C));
    memset(input->rightStateTimes24,0,sizeof(input->rightStateTimes24));
}
extern "C" void func_001A91E0(INPUT_CONTROLLER *input,INPUT_PRIORITY_NODE *node) {
    INPUT_PRIORITY_NODE *position=input->list1194.first;
    while(position&&position->priority14C>=node->priority14C)position=position->nextD4;
    func_0011AFC0(&input->list1194,position,node);
}
extern "C" int func_001A9260(INPUT_CONTROLLER *input) {
    INPUT_PRIORITY_NODE *node=func_001A91D8(input);
    INPUT_CONTROLLER_MODE *mode=0;
    if(node)mode=node->mode300;
    if(mode) {
        switch(mode->kind8) {
        case 3:case 6:return 1;
        case 13:
            if(mode->related20)return mode->related20->state198?6:5;
            return 5;
        case 12:return 2;
        case 8:return 3;
        case 2:
            INPUT_CONTROLLER_RESOLVED *resolved=func_001662A8(node);
            if(resolved)return resolved->value19C;
            break;
        }
    }
    return 0;
}
