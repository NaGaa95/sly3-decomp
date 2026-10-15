// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x3C]; int n3C; };
void func_00131568(struct S *p);
void func_00131B80(struct S *p) { func_00131568(p); p->n3C = 2; }
