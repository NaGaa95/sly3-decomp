// Clear the original embedded reference, first supplying actual float F12 zero to244CA8 and then the explicit null receiver to2BBCD8. Preserve the original address/object guards and reset its state word.
// Reference compiler shape: src/hand/func_00182FE8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Ref {void *object;int unknown;int state;};
struct S {char prefix[0x3E8];struct Ref reference;};
void func_00244CA8(void *receiver,float value);
void func_002BBCD8(void *reference,void *receiver);
void func_00205198(struct S *p){struct Ref *reference=&p->reference;if(reference&&reference->object){func_00244CA8(reference->object,0.0f);func_002BBCD8(reference,0);}p->reference.state=0;}
