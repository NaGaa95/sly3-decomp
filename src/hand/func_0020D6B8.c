// Perform the original timed attached-object update when ordered start/clock comparison permits it, then advance the receiver lifecycle. Both complete helpers consume receiver A0 only before their internally generated float/vector arguments.
// Reference compiler shape: src/hand/func_00181728.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x14]; float started; char unknown_18[0xEC]; void * object; };
extern float D_0036BB98;
void func_0020D3A0(void *receiver);
void func_0020C170(void *receiver);
void func_0020D6B8(struct S *p){if(p->started<=D_0036BB98&&p->object)func_0020D3A0(p);func_0020C170(p);}
