// Count the original sixteen-bit code units through the first zero terminator; A0 is the explicit input text pointer.
// Reference algorithm: src/hand/func_0012D058.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_00271700(const unsigned short *text){int length=0;while(*text){++text;++length;}return length;}
