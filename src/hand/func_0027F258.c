// Transform the explicit128-bit point, then return the original integer volume result.
// Reference algorithm: src/hand/func_001F3868.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
QWORD func_001C9428(void *first,void *second,QWORD value);
int func_0027F298(void *object,QWORD value);
int func_0027F258(void *object,QWORD value)
{
    return func_0027F298(object,func_001C9428(0,object,value));
}
