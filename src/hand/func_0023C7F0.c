// Resolve the original virtual record position and attach its global spatial resource through explicit vector and option inputs.
// Reference algorithm: src/hand/func_001B7000.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct R { char prefix[0x30];QWORD position; };
struct PMF { short adjustment;short reserved;struct R *(*method)(void *); };
struct S { char unknown_0[0xC]; struct PMF * vtable; };
void *func_001ED678(QWORD position,int option);
void func_0023C750(struct S *p,void *resource);
void func_0023C7F0(struct S *p){struct PMF *slot=p->vtable+36;struct R *record=slot->method((char *)p+slot->adjustment);func_0023C750(p,func_001ED678(record->position,1));}
