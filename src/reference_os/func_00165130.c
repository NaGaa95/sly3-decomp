// Sly 2 reference: src/hand/func_0014CDB0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct LSG { char pad[0x60]; };
int func_00164A10(void *pso, qword a, qword b, int c, struct LSG *plsg);
int func_00164D98(int c, struct LSG *alsg, int n, struct LSG *plsg, int cMax, struct LSG *alsg2, int f);
int func_00165130(qword a, qword b, int cso, void **apso, int cMax, struct LSG *alsg)
{
    int c = 0;
    int i;
    for (i = 0; i < cso; i++) {
        struct LSG *plsg = &alsg[c];
        int n = func_00164A10(apso[i], a, b, cMax - c, plsg);
        if (n)
            c = func_00164D98(c, alsg, n, plsg, cMax, alsg, 0);
    }
    return c;
}
