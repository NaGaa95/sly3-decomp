// Sly 2 reference: src/hand/func_001D87C0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef char *va_list;
#define va_arg_pch(ap) (*(char **)((ap += 8) - 8))
struct MSG { int cb; int nKind; };
typedef struct { int c; short *ash; } V;
typedef struct { int a[2]; char ht[1]; } H;
extern H D_004793C8;
void *func_001D25B0(struct MSG *);
int func_0021CB20(void *, char *);
static inline int NFind(H *ph, char *pch) { return func_0021CB20(ph->ht, pch); }
short func_00292480(char *);
void func_0021CBC0(char *pch, va_list ap, V *pv)
{
    va_list apSave = ap;
    char *pchT;
    int i;
    pv->c = 0;
    pv->ash = 0;
    for (pchT = pch; pchT; pchT = va_arg_pch(ap))
        pv->c++;
    if (pv->c) {
        struct MSG msg;
        msg.cb = pv->c * 2;
        msg.nKind = 0x10;
        pv->ash = func_001D25B0(&msg);
        ap = apSave;
        for (pchT = pch, i = 0; pchT; pchT = va_arg_pch(ap), i++) {
            int n = NFind(&D_004793C8, pchT);
            if (n == -1)
                pv->ash[i] = func_00292480(pchT);
            else
                pv->ash[i] = n;
        }
    }
}
