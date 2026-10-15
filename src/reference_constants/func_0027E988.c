// Reference algorithm: src/hand/func_002273F0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct BSP_NODE;
struct S { char pad[0xE4]; struct BSP_NODE *x; };
qword func_001C9428(void *first, struct S *second, qword point);
struct BSP_NODE *func_00119C90(struct BSP_NODE *node, unsigned int limit, qword point);
void func_0027E9D8(struct S *p, int f);
void func_0027E988(struct S *p, qword q)
{
    func_0027E9D8(p, func_00119C90(p->x, 0x7FFFFFFF, func_001C9428(0, p, q)) != 0);
}
