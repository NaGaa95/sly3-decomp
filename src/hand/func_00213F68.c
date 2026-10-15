// Perform inherited lifecycle reset, optional adjusted attached callback and sound/reference cleanup. Full1F3C80/1FCB20 consume receiver only and generate all downstream scalar inputs; actual244CA8 F12 zero and2BBCD8 null pointer are explicit. Nominal receiver-only indirect slot54 API remains provisional.
// Reference compiler shape: src/hand/func_001FBFB0.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct V {short delta;short unused;void (*method)(void *);};
struct Object {char prefix[0xC];struct V *vtable;};
struct Ref {void *object;int unknown;};
struct S { char unknown_0[0x430]; struct Object * object; char unknown_434[0x114]; struct Ref reference; };
void func_001F3C80(void *receiver);
void func_00244CA8(void *receiver,float value);
void func_002BBCD8(void *reference,void *object);
void func_00213F68(struct S *p){func_001F3C80(p);if(p->object)p->object->vtable[54].method((char *)p->object+p->object->vtable[54].delta);{struct Ref *reference=&p->reference;if(reference->object){func_00244CA8(reference->object,0.0f);func_002BBCD8(reference,0);}}}
