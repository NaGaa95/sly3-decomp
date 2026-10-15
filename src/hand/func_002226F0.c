// Write the original16-bit text for ID4F and append both actual8-bit literal strings through the8-bit-to16-bit converter. Caller supplies output pointer and all lookup/conversion inputs are explicit.
// Reference algorithm: src/hand/func_001A4E08.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[],D_003261B8[],D_003261C0[];
const unsigned short *func_00150630(void *context,int id);
unsigned short *func_00271730(unsigned short *output,const unsigned short *input);
unsigned short *func_00271828(unsigned short *output,const char *input);
void func_002226F0(unsigned short *output){func_00271730(output,func_00150630(D_00475480,0x4F));func_00271828(output,D_003261B8);func_00271828(output,D_003261C0);}
