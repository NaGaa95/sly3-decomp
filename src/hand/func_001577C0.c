// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x18]; void *p18; };
int func_00157800(struct S *p);
int func_00157950(void *p);
int func_001577C0(struct S *p) { if (!func_00157800(p)) return 0; return func_00157950(p->p18); }
