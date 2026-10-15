typedef int qword __attribute__((mode(TI)));
struct S { int a, b, c, d; qword q; };
void func_001B5370(void *, void *, qword *, qword *, float);
void func_001BB228(int, qword, int, qword, qword, int, float *, int, int);
float func_001BB6D0(struct S *s, float parameter) {
    float r; qword a, b;
    func_001B5370((void *)s->a, (void *)s->c, &a, &b, parameter);
    func_001BB228(s->b, s->q, s->c, a, b, 0, &r, 0, 0);
    return r;
}
