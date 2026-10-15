// Controller axis response and two independently queried inversion gates.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "input_interface.h"
#include "input_axis_config.h"
extern "C" void func_001A7B38(INPUT_INTERFACE *input,int index,float *outX,float *outY) {
    const INPUT_AXIS_CONFIG *config=func_001A7B20(index);
    float rawX,rawY;
    if(index==0||index==4) { rawX=input->rightX;rawY=input->rightY; }
    else { rawX=input->leftX;rawY=input->leftY; }
    float x=-__builtin_fabsf(rawX)*rawX*config->scaleX;
    int invert=config->invertX;
    if(input->FirstGate(index))invert=!invert;
    if(invert)x=-x;
    if(outX)*outX=x;
    float y=__builtin_fabsf(rawY)*rawY*config->scaleY;
    invert=config->invertY;
    if(input->SecondGate(index))invert=!invert;
    if(invert)y=-y;
    if(outY)*outY=y;
}
