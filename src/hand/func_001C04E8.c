// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct F { int a[4]; qword q; };
void *func_00292034(void *, int, int);
void func_001C0538(void *, struct F *);
void func_001C04E8(void *p, qword q) { struct F f; func_00292034(&f, 0, sizeof f); f.q = q; func_001C0538(p, &f); }
