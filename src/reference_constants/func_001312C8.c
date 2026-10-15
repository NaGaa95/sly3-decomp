// Reference algorithm: src/hand/func_0012EDE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct T { char pad[0xD0]; int c; int pad2; void **ap; } T;
void func_001C85C0(T *p);
void func_00244CA8(void *pv, float g);
void func_002BBCD8(void **pp, int n);
void func_001312C8(T *p)
{
    int i;
    func_001C85C0(p);
    for (i = 0; i < p->c; i++) {
        void **pp = (void **)((i << 2) + (int)p->ap);
        if (pp && *pp) {
            func_00244CA8(*pp, 0.0f);
            func_002BBCD8(pp, 0);
        }
    }
}
