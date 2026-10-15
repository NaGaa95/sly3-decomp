// Map unsigned source bytes through the original game-character table.
// Write a sixteen-bit terminator and return the destination.
// SLY3_CFLAGS: -Os -G0
extern const unsigned short D_00349D88[256];
unsigned short *func_002717E0(unsigned short *destination,const char *text){const unsigned char *source=(const unsigned char *)text;unsigned short *output=destination;while(*source){*output++=D_00349D88[*source++];}*output=0;return destination;}
