// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; int n30; };
void func_00238970(struct S *p);
void func_00252E40(void *p, int n);
void func_001344A0(struct S *p) { func_00238970(p); func_00252E40(p->p10, 0x2B); p->n30 = -1; }
