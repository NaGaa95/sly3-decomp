// Copy the original sixteen-bit game text including its terminator, using twice the number of code units plus one; return the explicit destination pointer.
// Reference algorithm: src/hand/func_001E1560.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_00271700(const unsigned short *text);
void func_001D2898(void *destination,const void *source,int byte_count);
unsigned short *func_00271730(unsigned short *destination,const unsigned short *source){int length=func_00271700(source);func_001D2898(destination,source,2*(length+1));return destination;}
