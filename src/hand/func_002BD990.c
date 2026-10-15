// Optionally refresh the original receiver with the explicit option and return the embedded data address inside its referenced record.
// Reference algorithm: src/hand/func_001B34D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xD4]; char * record; };
void func_002BD8C8(void *receiver,int option);
void *func_002BD990(struct S *p,int option){if(option==1)func_002BD8C8(p,0);return p->record+0x10;}
