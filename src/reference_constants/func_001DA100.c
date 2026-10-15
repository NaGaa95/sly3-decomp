// Reference algorithm: src/hand/func_001BC050.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1C4]; char dl[0x24]; int f1e8; };
void func_00238970(struct S *p);
void func_00252E40(void *pdl, int ib);
void func_001DA100(struct S *p)
{
    func_00238970(p);
    *(int *)((char *)p + 0x30) = -1;
    func_00252E40(*(void **)((char *)p + 0x10), 0x39);
}
