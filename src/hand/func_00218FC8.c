// Unpack the explicit reference into both original receiver fields through the six-field historical API and release the temporary output reference.
// Reference algorithm: src/hand/func_001A5BF0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Ref { short tag;short reserved;int value; };
void func_0024B330(struct Ref *output,struct Ref *input,int type,int format,int *count,void **values);
void func_0012BC20(struct Ref *reference);
void func_00218FC8(void *p,struct Ref *input){struct Ref result;func_0024B330(&result,input,1,13,(int *)((char *)p+0x214),(void **)((char *)p+0x1E0));func_0012BC20(&result);}
