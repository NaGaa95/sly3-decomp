// Reference algorithm: src/hand/func_001B0160.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int a; void *pv; int pad[5]; };
struct P { int pad[8]; struct E ae[1]; };
struct PX { char pad[0x1FC]; int f; int n; };
extern char D_003459F0[];
int func_0021DD30(struct P *p);
int func_001D4738(struct P *p)
{
    int n;
    struct E *pe;
    if (!func_0021DD30(p)) return 0;
    n = *(int *)((char *)p + 0x38);
    if (n <= 0) return 0;
    pe = &p->ae[n];
    if (((struct PX *)p)->f == 1 && n < ((struct PX *)p)->n)
        pe = &p->ae[((struct PX *)p)->n];
    return pe->pv == D_003459F0;
}
