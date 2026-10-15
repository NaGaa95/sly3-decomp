// Supply both actual scene object/receiver pointers and invoke the adjusted virtual selector5 with four explicit null inputs. The nominal six-input indirect callback API remains provisional.
// Reference compiler shape: src/hand/func_00147220.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *,int,void *,void *,void *,void *);};
struct S { char unknown_0[0xC]; struct V * vtable; };
void func_001C8FB0(void *object,void *receiver);
void func_0027FA70(struct S *p,void *object){func_001C8FB0(object,p);p->vtable[3].method((char *)p+p->vtable[3].delta,5,0,0,0,0);}
