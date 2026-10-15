// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x18]; void *p18; };
int func_001D96F8(struct S *p);
int func_001D7F90(void *p);
int func_001D96B8(struct S *p) { if (!func_001D96F8(p)) return 0; return func_001D7F90(p->p18); }
