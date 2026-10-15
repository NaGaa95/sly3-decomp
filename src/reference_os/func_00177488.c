// Sly 2 reference: src/hand/func_00159118.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword aq[4]; } M4;
typedef struct B7 { qword aq[7]; } B7;
extern M4 D_0036BD50;
extern B7 D_0036BD90;
struct S { int a; int b; int pad[2]; M4 m; B7 b7; char pad2[0x100 - 0xC0]; };
void *func_00292034(void *pv, int b, int cb);
void func_00177488(struct S *p)
{
    func_00292034(p, 0, sizeof(struct S));
    p->a = 1;
    p->b = -1;
    p->m = D_0036BD50;
    p->b7 = D_0036BD90;
}
