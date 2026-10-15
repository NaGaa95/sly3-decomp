// Notify the adjusted virtual receiver with literal4, then update both actual records when the secondary value exists. Nominal virtual callback API remains provisional; both direct notification arguments are explicit.
// Reference algorithm: src/hand/func_001FBFB0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *,int);};
struct S { char unknown_0[0xC]; struct V * vtable; char unknown_10[0x38]; void * first; void * second; char unknown_50[0x88]; void * value; void * record; };
void func_0028F260(void *receiver,void *record);
void func_0023E228(struct S *p){if(p->record){p->vtable[51].method((char *)p+p->vtable[51].delta,4);if(p->value){func_0028F260(p,p->first);func_0028F260(p,p->second);}}}
