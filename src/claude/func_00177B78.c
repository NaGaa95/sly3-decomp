// SLY3_CFLAGS: -Os -G0
// Sly 2 reference: /home/claude/decomp src/hand/func_0015C5C8.c.
struct O { char pad[0x128]; void *p100; void *p104; };
void func_0013BD88(void *pv, void *po);
void func_00177B78(struct O *o, int msgid, void *pv)
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
