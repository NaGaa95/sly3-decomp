// Synchronize the stored geometry context when its generation differs, then return all128 cached value bits. Complete18B1E0 consumes only context A0 and sets its other internal inputs; no implicit incoming argument is used.
// Reference algorithm: src/hand/func_001CB2E0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Owner {char prefix[0xA4];int generation;};
struct Context {struct Owner *owner;char prefix[0xC0-4];int generation;};
struct S { char unknown_0[0x224]; QWORD * value; char unknown_228[0x60]; struct Context * context; };
void func_0018B1E0(struct Context *context);
QWORD func_00250600(struct S *p){struct Context *context=p->context;if(context->generation!=context->owner->generation)func_0018B1E0(context);return *p->value;}
