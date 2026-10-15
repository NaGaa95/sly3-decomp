// Append all explicit command words and float value with the original absent field set to -1.
// Reference algorithm: src/hand/func_00208BB0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_00283278(void *object,int first,int absent,int second,int third,int fourth,float value);
void func_00283310(void *object,int first,int second,int third,int fourth,float value)
{
    func_00283278(object,first,-1,second,third,fourth,value);
}
