// Release the embedded reference and linked record, then return the receiver to its actual pool when requested. Both cleanup methods consume explicit A0 only; pool helper consumes both actual pointer inputs.
// Reference algorithm: src/hand/func_00139318.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_004D2F10[];
void func_0012BC20(void *reference);
void func_002B4E48(void *receiver);
void func_0011E1F0(void *pool,void *receiver);
void func_002BB798(void *receiver,int flags){func_0012BC20((char *)receiver+8);func_002B4E48(receiver);if(flags&1)func_0011E1F0(D_004D2F10,receiver);}
