// Construct the output reference from the explicit input record count, original type descriptor and embedded value data.
// Reference algorithm: src/hand/func_001B34D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Ref { short tag;short reserved;int value; };
struct S { char unknown_0[0x58]; int count; };
struct Ref *func_0024AEF8(struct Ref *output,int count,int type,void *values);
struct Ref *func_0021A780(struct Ref *output,struct S *values){func_0024AEF8(output,values->count,0x2058,(char *)values+0x44);return output;}
