// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x68]; int fl; };
void func_00248598(struct S *p, int f, int fSet) { if (fSet) p->fl |= f; else p->fl &= ~f; }
