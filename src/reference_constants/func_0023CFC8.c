// Reference algorithm: src/hand/func_001F3FB0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct A { char pad[0x50]; void *node; };
void func_00292034(void *p, int c, int cb);
void *func_0023CFC8(struct A *p, float *pm)
{
    if (pm) {
        func_00292034(pm, 0, 0x40);
        pm[0] = pm[5] = pm[10] = pm[15] = 1.0f;
    }
    return p->node;
}
