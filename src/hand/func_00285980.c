// Forward receiver/event/record, then dispatch matching event12 with the adjusted receiver and its explicit payload A1.1F4278 consumes receiver/event, while supplied record A2 is caller-derived unused through empty13BEC0. Payload nominal pointer and indirect return type remain provisional.
// Reference algorithm: src/hand/func_001B10D0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { short delta;short unused;void (*method)(void *,void *); };
struct Event { int key;int unused;void *payload; };
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x2D4]; int key; };
void func_001F4278(void *receiver,int event,struct Event *record);
void func_00285980(struct S *p,int event,struct Event *record){func_001F4278(p,event,record);if(event==12 && record->key==p->key)p->vtable[78].method((char *)p+p->vtable[78].delta,record->payload);}
