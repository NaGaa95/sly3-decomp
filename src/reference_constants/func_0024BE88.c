// Reference algorithm: src/hand/func_00201F90.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
extern char D_00475480[];
struct S { char pad[0x20]; qword v; char pad2[0xB8 - 0x30]; int f; };
int func_0017E208(void *game, int flags, int kind, void *owner, int limit, void **output);
int func_0027F258(void *object, qword point);
void func_0024BE88(struct S *p)
{
    void *a[16];
    int n, i;
    int *pa;
    p->f = 0;
    n = func_0017E208(D_00475480, 0x505, 0x16, 0, 16, a);
    for (i = 0; i < n; i++) {
        if (func_0027F258(a[i], p->v)) {
            p->f = 1;
            break;
        }
    }
}
