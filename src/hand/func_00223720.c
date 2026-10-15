// Combine both object identifier lists into the accumulated predicate result.
// Reference algorithm: src/hand/func_001DE2D8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct {
    char pad[0x130];
    int c1;
    void *a1[7];
    int c2;
    void *a2[8];
} OBJ;
int func_001C8768(void *, void *);
int func_0013B500(void *, void *);
int func_0013CD00(int, int);
int func_00223720(OBJ *p, void *x)
{
    int i, j;
    int r = 1;
    for (i = 0; i < p->c1; i++) {
        if (func_001C8768(x, p->a1[i]))
            r = func_0013CD00(r, 2);
    }
    for (j = 0; j < p->c2; j++) {
        if (func_0013B500(x, p->a2[j]))
            r = func_0013CD00(r, 2);
    }
    return r;
}
