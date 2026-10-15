// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct E { int a[4]; };
void func_00254FE0(struct E *pe);
void func_002539E0(void *p, struct E *pe) { int i; for (i = 25; i >= 0; i--) { func_00254FE0(pe); pe++; } }
