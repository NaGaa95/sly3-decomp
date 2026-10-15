// Use the original embedded-record status unless its1000 bit requests the receiver-specific status; both helpers consume only explicit A0 and their actual integer results are returned.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
unsigned int func_00238888(void *record);
unsigned int func_0024E2A8(void *receiver);
unsigned int func_00256CB0(void *receiver){unsigned int result=func_00238888((char *)receiver+0x29C);if(!(result&0x1000))return result;return func_0024E2A8(receiver);}
