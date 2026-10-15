// Reference algorithm: src/hand/func_001E1DB8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct S {
    char pad[0x1C];
    void *owner;
}
S;
extern struct G D_00475480;
void *func_0017E1B8(struct G *g, int k, int id, void *owner);
int func_0013B500(void *p, int k);
void *func_001FBEC0(void *p);
void *func_00226770(S *p, int id) {
    void *q;
    if (id == -1) {
        q = 0;
    }
    else {
        q = func_0017E1B8(&D_00475480, 4, id, p->owner);
        if (q && func_0013B500(q, 8)) q = func_001FBEC0(q);
    }
    return q;
}
