// Perform inherited receiver cleanup and both adjusted virtual updates outside original state6, passing explicit sentinel -1 to the first. Nominal distinct indirect callback APIs are provisional; no implicit direct input is used.
// Reference compiler shape: src/hand/func_00132238.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *,int);};
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x120]; int state; };
void func_0023BBE0(void *receiver);
void func_00276EC8(struct S *p){func_0023BBE0(p);if(p->state!=6){p->vtable[80].method((char *)p+p->vtable[80].delta,-1);((void (*)(void *))p->vtable[9].method)((char *)p+p->vtable[9].delta);}}
