// Apply the adjusted attached receiver selection when original state1 is active. The nominal receiver-only integer virtual API is provisional; actual receiver/selection inputs to215388 are explicit.
// Reference compiler shape: src/hand/func_00211CA8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;int (*method)(void *);};
struct Object {struct V *vtable;};
struct S { char unknown_0[0x1B8]; int state; char unknown_1BC[0x334]; struct Object * object; };
void func_00215388(void *receiver,int selection);
void func_002151E8(struct S *p){if(p->state==1&&p->object)func_00215388(p,p->object->vtable[1].method((char *)p->object+p->object->vtable[1].delta));}
