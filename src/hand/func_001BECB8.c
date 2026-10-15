// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { int pad[3]; int c; int d; };
void func_001BECB8(struct S *s, int a) { if (a) s->d = a; else s->d = s->c; }
