// Reference algorithm: src/hand/func_0015C5C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct O { char pad[0xF0]; void *p100; void *p104; };
void func_0013BD88(void *pv, void *po);
void func_0017A280(struct O *o, int msgid, void *pv)
{
    if (msgid == 1) {
        if (pv == o->p100) {
            func_0013BD88(pv, o);
            o->p100 = 0;
        } else if (pv == o->p104) {
            func_0013BD88(pv, o);
            o->p104 = 0;
        }
    }
}
