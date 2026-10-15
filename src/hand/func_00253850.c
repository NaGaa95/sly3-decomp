// 253690 explicitly consumes A0 object,A1 mask,A2 value,A3 option,A4 record pointer. Outer four actual inputs are explicit and A4 is derived from object+AE0. Compatible with the existing complete five-input typed hand implementation.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
void func_00253690(void *object,int mask,int value,int option,void *records);
void func_00253850(void *object,int mask,int value,int option){func_00253690(object,mask,value,option,(char *)object+0xAE0);}
