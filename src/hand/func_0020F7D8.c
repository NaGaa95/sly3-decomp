// Update the inherited object and apply its evaluated128-bit record value to the present owner.
// Reference algorithm: src/hand/func_00224068.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef unsigned int QWORD __attribute__((mode(TI)));
struct M3 { QWORD vectors[3]; };
struct S { char prefix[0x4C]; void *record; char unknown[0x1D4-0x50]; void *owner; };
void func_0023D338(struct S *object,const struct M3 *source);
QWORD func_0011D3C0(void *record);
void func_0012F4F8(void *owner,QWORD value);
void func_0020F7D8(struct S *object,const struct M3 *source)
{
    func_0023D338(object,source);
    if(object->owner)func_0012F4F8(object->owner,func_0011D3C0(object->record));
}
