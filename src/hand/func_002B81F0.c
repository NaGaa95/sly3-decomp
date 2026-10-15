// Construct the inherited object, install its vtable, and clear the embedded 16-byte record.
// Reference algorithm: src/hand/func_001DB7A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00358E18[];
struct S { char pad[0xC]; void *vt; char unknown[0x20]; char record[0x10]; };
struct S *func_002B58E8(struct S *p);
void *func_00292034(void *p, int value, int size);
struct S *func_002B81F0(struct S *p)
{
    func_002B58E8(p);
    p->vt = D_00358E18;
    func_00292034(p->record, 0, sizeof(p->record));
    return p;
}
