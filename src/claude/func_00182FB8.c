// SLY3_CFLAGS: -Os -G0
typedef struct { unsigned int pad[0x1000 / 4]; unsigned int csr; } GSREG_t;
extern int D_0036DBEC;
extern int D_0036C690;
#define GS ((volatile GSREG_t *)0x12000000)
int func_00182FB8(void) { volatile GSREG_t *g; if (D_0036DBEC & 3) return 0; g = GS; if (D_0036C690 != 0) return 0; return ((g->csr >> 13) & 1) ^ 1; }
