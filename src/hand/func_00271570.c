// Format the explicit16-bit text inputs with the original unlimited capacity and append the terminating zero.
// Reference algorithm: src/hand/func_001F3868.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_002710E8(unsigned short *output,int capacity,const unsigned short *format,const void *arguments);
int func_00271570(unsigned short *output,const unsigned short *format,const void *arguments){int length=func_002710E8(output,-1,format,arguments);output[length]=0;return length;}
