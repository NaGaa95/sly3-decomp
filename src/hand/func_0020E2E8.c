// Invoke the original empty inherited stub and store the explicit additional value; the caller-derived source formal is unused by this original body.
// Reference algorithm: src/hand/func_001A2388.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xF4]; int value; };
void func_0020BDA8(void);
void func_0020E2E8(struct S *object,void *source,int value)
{
    (void)source;func_0020BDA8();object->value=value;
}
