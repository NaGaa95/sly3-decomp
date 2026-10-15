// Update the inherited object from the explicit matrix and extract both stored values through its original virtual record getter.
// Reference algorithm: src/hand/func_0012E6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct M3 { QWORD rows[3]; };
struct PMF { short adjustment;short reserved;void *(*method)(void *); };
struct S { char unknown_0[0xC]; struct PMF * vtable; };
void func_0023D338(struct S *object,const struct M3 *source);
void func_0011D048(void *record,float *first,float *second);
void func_0026CC78(struct S *object,const struct M3 *source)
{
    struct PMF *slot;void *record;
    func_0023D338(object,source);
    slot=object->vtable+36;record=slot->method((char *)object+slot->adjustment);
    func_0011D048(record,(float *)((char *)object+0x1DC),(float *)((char *)object+0x1E0));
}
