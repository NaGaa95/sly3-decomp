// Convert the explicit input reference into the receiver output array, release the local reference and notify the adjusted receiver.24B330 consumes A0,A1,A2,A4,A5; historical format10 A3 is supplied but unused by the complete original callee. Receiver-only indirect method signature remains provisional.
// Reference algorithm: src/hand/func_00212828.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { short delta; short unused; int (*method)(void *); };
struct S { char unknown_0[0xC]; struct V * vtable; };
struct Ref { short tag;short unused;void *value; };
struct Ref *func_0024B330(struct Ref *result,struct Ref *input,int capacity,int format,int *count,void *output);
void func_0012BC20(struct Ref *ref);
void func_00260D78(struct S *p,struct Ref *input){struct Ref result;int count;func_0024B330(&result,input,0x10,10,&count,(char *)p+0xBC);func_0012BC20(&result);p->vtable[56].method((char *)p+p->vtable[56].delta);}
