// Reference algorithm: src/hand/func_00227380.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xD0]; int a; int b; char c[0x10]; char d[4]; };
void func_00290438(struct S *p, void *q);
int func_001190A8(void *q);
void func_001193F8(void *q, void *a);
void func_00119640(void *q, void *a, void *b);
void func_001519C8(struct S *p, void *q);
void func_0027E918(struct S *p, void *q)
{
    func_00290438(p, q);
    p->a = func_001190A8(q);
    func_001193F8(q, p->d);
    func_00119640(q, p->d, p->c);
    func_001519C8(p, q);
}
