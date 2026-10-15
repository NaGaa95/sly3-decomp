// Update the inherited state and set the embedded collection owner explicitly.
// Reference algorithm: src/hand/func_00174920.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0023F400(void *p, void *source);
void func_00238500(void *record, void *owner);
void func_0024D9A8(void *p, void *source)
{
    func_0023F400(p, source);
    func_00238500((char *)p + 0x29C, p);
}
