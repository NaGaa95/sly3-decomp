// Preserve the current packed position then replace it with the actual attached-object query position30. The adjusted receiver-only virtual method returns a record pointer; nominal method type remains provisional.
// Reference algorithm: src/hand/func_00212780.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Record {QWORD basis[3];QWORD position;};
struct V {short delta;short unused;struct Record *(*method)(void *);};
struct Object {char prefix[0xC];struct V *vtable;};
struct S { char unknown_0[0x70]; QWORD position; QWORD previous; char unknown_90[0x60]; struct Object * object; };
void func_0020D7A0(struct S *p){struct Record *record;p->previous=p->position;record=p->object->vtable[36].method((char *)p->object+p->object->vtable[36].delta);p->position=record->position;}
