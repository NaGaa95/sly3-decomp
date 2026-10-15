// Reference algorithm: src/hand/func_0013B1C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct N { char pad[0x10]; struct N *pnext; };
extern int D_00320278[4];
int func_0013B500(struct N *, int);
int func_0014C778(void *unused, struct N *pn) {
    unsigned int i;
    for (; pn; pn = pn->pnext) {
        for (i = 0; i < 5; i++) {
            if (func_0013B500(pn, D_00320278[i])) return 0;
        }
    }
    return 1;
}
