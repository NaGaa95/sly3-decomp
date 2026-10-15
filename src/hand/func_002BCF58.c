// Optionally refresh the original receiver and return the nested record value.
// Reference algorithm: src/hand/func_001B34D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x30]; int value; };
struct S { char unknown_0[0xD4]; struct R * record; };
void func_002BCE58(struct S *p,int option);
int func_002BCF58(struct S *p,int option){if(option==1)func_002BCE58(p,1);return p->record->value;}
