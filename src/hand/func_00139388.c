// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct K { int a; int b; };
extern struct K D_0031F9F0;
extern char D_00475480[];
struct S { void *pframe; };
void func_0023E110(struct S *);
void *func_00129B58(void *, int, int);
void func_0015DCD0(void *, void *, struct K, int);
void func_00139388(struct S *p) {
    func_0023E110(p);
    if (p->pframe && func_00129B58(p->pframe, 5, 1)) func_0015DCD0(D_00475480, p, D_0031F9F0, 0);
}
