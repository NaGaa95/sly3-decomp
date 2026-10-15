// SLY3_ASFIX: engine-exit-slots
// Search original16-bit text for the narrowed character, including the terminator for a zero needle.
// The following unrelated SP+30 tail is excluded by independent original-boundary review.
// SLY3_CFLAGS: -Os -G0
unsigned short *func_002718A0(unsigned short *text,int character){unsigned short *result;unsigned short value;character&=65535;result=text;for(;;){value=*result;if(value==character)break;if(value)++result;else{result=0;break;}}return result;}
