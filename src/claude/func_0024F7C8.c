// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_00205478.c (7 slots in Sly 3).
extern char D_00474FF0[];
extern char D_00475480[];
struct S { char pad[0x2C8]; int a[7]; };
int func_00246F30(void *p, int i);
void *func_0017E1B8(void *p, int a, int b, struct S *ps);
void *func_00239A10(void *x, struct S *ps);
void func_002397E8(void *x, struct S *ps, int a, int b, void **ppv);
void func_0024F7C8(struct S *p, int mask)
{
    int i;
    for (i = 0; i < 7; i++) {
        int bit = 0;
        if ((unsigned int)i < 7)
            bit = 1 << i;
        if (mask & bit) {
            if (++p->a[i] < 2) {
                int id = func_00246F30(D_00474FF0, i);
                void *x = func_0017E1B8(D_00475480, 4, id, p);
                if (x) {
                    void *y = func_00239A10(x, p);
                    if (!y)
                        func_002397E8(x, p, -1, 9, &y);
                }
            }
        }
    }
}
