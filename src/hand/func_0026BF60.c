// Initialize the inherited receiver, resolve13 actual descriptor records with nullable context, and apply the original packed-vector/default option updates. Every actual scalar/pointer/vector input is explicit.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
extern char D_00349CD0[];
extern QWORD D_00317560;
void func_001F3BF8(void *receiver);
void func_001C8970(void *receiver,int count,void *fields,void *context);
void func_0023ED58(void *receiver,QWORD value);
void func_0023EC98(void *receiver,int option);
void func_0026BF60(void *receiver){func_001F3BF8(receiver);func_001C8970(receiver,13,D_00349CD0,0);func_0023ED58(receiver,D_00317560);func_0023EC98(receiver,1);}
