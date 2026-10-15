// Initialize the inherited receiver, set original bit2 in a pointer-backed or inline tagged word, enter state1 and invoke the adjusted slot9 update. The tagged low-bit representation is explicit; nominal indirect receiver-only callback API remains provisional.
// Reference compiler shape: src/hand/func_00174950.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *);};
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x2C]; unsigned int tagged; };
void func_001C7340(void *receiver);
void func_001C9118(void *receiver,int state);
void func_00219660(struct S *p){unsigned int value;func_001C7340(p);value=p->tagged;if((value^1)&1)*(unsigned int *)value|=2;else p->tagged=value|2;func_001C9118(p,1);p->vtable[9].method((char *)p+p->vtable[9].delta);}
