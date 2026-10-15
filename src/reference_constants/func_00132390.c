// Reference algorithm: src/hand/func_0021BBD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x15C]; int f; };
void func_00131770(struct S *p);
void func_00132C58(struct S *p, int state);
void func_00238A38(void *p);
void func_00132390(struct S *p)
{
    func_00131770(p);
    func_00132C58(p, 4); func_00238A38(p);
}
