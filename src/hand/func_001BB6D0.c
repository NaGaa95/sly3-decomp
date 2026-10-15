// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct S { int a, b, c, d; qword q; };
void func_001B5370(int, int, qword *, qword *);
void func_001BB228(int, qword, int, qword, qword, int, float *, int, int);
float func_001BB6D0(struct S *s) {
    float r; qword a, b;
    func_001B5370(s->a, s->c, &a, &b);
    func_001BB228(s->b, s->q, s->c, a, b, 0, &r, 0, 0);
    return r;
}
