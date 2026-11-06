// Remove every occurrence of x from an int list (count at +0x3B4 / +0x3CC). Cf. Sly 2 src/hand/func_00208A90.c.
void *func_00291F38(void *d, void *s, int n);
struct S1 { char pad[0x3B4]; int n; int a[1]; };
struct S2 { char pad[0x3CC]; int n; int a[1]; };
void func_00254348(struct S1 *p, int x)
{
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->a[i] == x) {
            func_00291F38(p->a + i, p->a + i + 1, (p->n - i) * 4 - 4);
            i--;
            p->n--;
        }
    }
}
void func_00254428(struct S2 *p, int x)
{
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->a[i] == x) {
            func_00291F38(p->a + i, p->a + i + 1, (p->n - i) * 4 - 4);
            i--;
            p->n--;
        }
    }
}
