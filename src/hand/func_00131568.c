// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x30]; int n30; int pad2[2]; int n3C; };
void func_00238970(struct S *p);
void func_00131568(struct S *p) { func_00238970(p); p->n3C = 0; p->n30 = -1; }
