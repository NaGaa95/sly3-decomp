// Resolve the original nonempty tagged reference into an explicit local eight-byte result, retain its value word across cleanup and return it. Nominal returned-word semantic type is provisional; every actual helper output/input/context pointer is explicit.
// Reference compiler shape: src/hand/func_00124640.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Ref {int kind;int value;};
struct S {char prefix[0xB0];struct Ref reference;};
extern char D_00468D30[];
struct Ref *func_002BC010(struct Ref *result,struct Ref *reference,void *context);
void func_0012BC20(void *reference);
int func_002835D0(struct S *p){if(p->reference.kind){struct Ref result;int value;func_002BC010(&result,&p->reference,D_00468D30);value=result.value;func_0012BC20(&result);return value;}return 0;}
