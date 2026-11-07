// Sly 2 counterpart: sceSifExecNotifyHandler (decomp src/lib/sceSifExecNotifyHandler.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { void (*func)(void *, void *); void *arg; void *gp; int pad; } CmdData;
extern CmdData D_004CF088[];
extern CmdData *D_0034B670;
extern int D_0034B674;
static inline void *SetGP(void *gp)
{
    void *old;
    __asm__ volatile("move %0, $gp\n\tmove $gp, %1" : "=&r"(old) : "r"(gp) : "memory");
    return old;
}
static inline void *GetGP(void)
{
    void *gp;
    __asm__ volatile("move %0, $gp" : "=r"(gp));
    return gp;
}
void *func_002995A0(int sys, void *data)
{
    CmdData *p;
    int n;
    void *gp;
    if (sys) {
        n = 0x20;
        p = D_004CF088;
    } else {
        p = D_0034B670;
        n = D_0034B674;
    }
    gp = GetGP();
    if (n > 0) {
        CmdData *q = p;
        int i = n;
        do {
            if (q->func) {
                SetGP(q->gp);
                q->func(data, q->arg);
            }
            i--;
            q++;
        } while (i != 0);
    }
    return SetGP(gp);
}
