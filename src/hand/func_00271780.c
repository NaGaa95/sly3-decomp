// Append original sixteen-bit game-text units, copying the source terminator.
// Both lengths and all three CopyAb inputs are explicit.
// SLY3_CFLAGS: -Os -G0
int func_00271700(const unsigned short *text);
void func_001D2898(void *destination,const void *source,unsigned int bytes);
unsigned short *func_00271780(unsigned short *destination,const unsigned short *source){int destination_length=func_00271700(destination);int source_length=func_00271700(source);func_001D2898(destination+destination_length,source,2*(source_length+1));return destination;}
