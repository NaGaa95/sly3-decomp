// Construct the inherited object, install its vtable, and initialize both embedded 32-byte records.
// Reference algorithm: src/hand/func_001DB7A8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035D8E0[];
struct R { char bytes[0x20]; };
struct S { char pad[0xC]; void *vt; char unknown[0x30]; struct R first; struct R second; };
struct S *func_002B58E8(struct S *p);
void func_002B8750(struct R *record);
struct S *func_002B83C0(struct S *p)
{
    func_002B58E8(p);
    p->vt = D_0035D8E0;
    func_002B8750(&p->first);
    func_002B8750(&p->second);
    return p;
}
