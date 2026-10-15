// Release the embedded owner and reference, unlink the actual receiver, and return it to the original pool when deletion flag1 is set. All actual helper inputs and outer deletion flags are explicit.
// Reference algorithm: src/hand/func_00132DE0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_002BADA0(void *receiver,int flags);
void func_0012BC20(void *reference);
void func_002B3F48(void *receiver);
void func_0011E1F0(void *pool,void *allocation);
extern char D_004D2BB0[];
void func_002BACE0(void *receiver,int flags){func_002BADA0((char *)receiver+0x14,2);func_0012BC20((char *)receiver+0xC);func_002B3F48(receiver);if(flags&1)func_0011E1F0(D_004D2BB0,receiver);}
