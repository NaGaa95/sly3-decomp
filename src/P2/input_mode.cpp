// Controller mode/version transition with original scalar and timestamp state.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_mode.h"
extern "C" void func_001A8780(INPUT_CONTROLLER *input,int mode,int version) {
    if(mode==input->mode1050&&version==input->version1054)return;
    if(!version) { input->reset104C=0;mode=1; }
    if(input->version1054<3&&version>=3)
        func_002109F8(input->callback1124,input->port1044,input->slot1048);
    if((input->version1054==4&&version!=4)||(input->version1054!=4&&version==4))
        memset(input->pressure1118,0,sizeof(input->pressure1118));
    if((input->mode1050==3&&mode!=3)||(input->mode1050!=3&&mode==3)) {
        input->reset105C=0;
        input->active106C=0xFFFF;
        input->rightReset10E4=0;
        input->leftReset10B8=0;
        input->previous1068=0;
        input->held18=0;
        input->Consume(0xFFFF);
        memset(input->pressure1118,0,sizeof(input->pressure1118));
        input->rightX=input->rightY=input->rightAmount=input->rightScalar10E0=input->leftX=input->leftY=input->leftAmount=input->leftScalar10B4=0.0f;
        input->leftStateTimes1C[0]=input->rightStateTimes24[0]=D_0036BB98.now;
        for(unsigned int i=0;i<4;++i) {
            input->rightRanges10E8[i].minimum=-0.75f;
            input->leftRanges10BC[i].minimum=-0.75f;
            input->rightRanges10E8[i].maximum=0.75f;
            input->leftRanges10BC[i].maximum=0.75f;
        }
    }
    input->mode1050=mode;
    input->version1054=version;
    input->time1058=D_0036BBD8.value;
}
