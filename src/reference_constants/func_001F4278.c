// Reference algorithm: src/hand/func_001C3E20.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x150]; void *p174; };
void func_0013BEC0(struct S *p, int n);
void func_00244CA8(void *p, float g);
void func_002BBCD8(void **pp, int n);
void func_001F4278(struct S *p, int n)
{
    func_0013BEC0(p, n);
    if (n == 7) {
        void **pp = &p->p174;
        if (pp && *pp) {
            func_00244CA8(*pp, 0.0f);
            func_002BBCD8(pp, 0);
        }
    }
}
