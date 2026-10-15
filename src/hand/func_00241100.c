// Forward the five actual GP owner/flags/identifier/active/receiver inputs through the original nine-argument initializer, with two complete128-bit default values and explicit nullable stack output. The complete callee input graph was independently reviewed in R11; nominal outer void API remains provisional.
// Reference compiler shape: src/hand/func_001A5020.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
extern QWORD D_00317560;
void func_00240CB0(void *receiver,int option,void *owner,int flags,int identifier,int active,QWORD first,QWORD second,void *output);
void func_00241100(void *owner,int flags,int identifier,int active,void *receiver){func_00240CB0(receiver,0,owner,flags,identifier,active,D_00317560,D_00317560,0);}
