// Set original initial and transition states, registering self with explicit sentinel selection and actual F12 time, then attach the receiver to its original resource. Every direct pointer/int/float input is explicit.
// Reference compiler shape: src/hand/func_001A4E08.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
extern float D_00325CBC;
extern void *D_00468D24;
void func_00215FD0(void *receiver,int state);
void func_001F4DD8(void *receiver,void *object,int selection,float time);
void func_002159D8(void *receiver,int state);
void func_0021A450(void *object,void *receiver);
void func_00218BA0(void *receiver){func_00215FD0(receiver,3);func_001F4DD8(receiver,receiver,-1,D_00325CBC);func_002159D8(receiver,7);func_0021A450(D_00468D24,receiver);}
