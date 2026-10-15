// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0 -fstrict-aliasing
typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;
typedef struct {
    u_char sts, std, mfd, rcyc;
    u_short express, notify;
    u_short sqwc, tqwc;
    void *rbadr;
    u_int rbmsk;
} RuntimeDmaEnvironment;
#define D_CTRL ((volatile u_int *)0x1000E000)
#define D_PCR  ((volatile u_int *)0x1000E020)
#define D_SQWC ((volatile u_int *)0x1000E030)
#define D_RBSR ((volatile u_int *)0x1000E040)
#define D_RBOR ((volatile u_int *)0x1000E050)
extern const u_char D_0032B4F8[]; /* sts map */
extern const u_char D_0032B508[]; /* std map */
extern const u_char D_0032B518[]; /* mfd map */
extern RuntimeDmaEnvironment D_004D0C00;
int func_0029FB40(RuntimeDmaEnvironment *env)
{
    u_int ctrl, pcr, sqwc, rbsr, rbor;
    ctrl = *D_CTRL;
    pcr = *D_PCR;
    sqwc = *D_SQWC;
    rbor = *D_RBOR;
    rbsr = *D_RBSR;

    if (env->sts >= 10) return -1;
    if (env->std >= 10) return -2;
    if (env->mfd >= 10) return -3;
    if (env->rcyc >= 7) return -4;
    ctrl = (ctrl & ~0x30) | (D_0032B4F8[env->sts] << 4);
    ctrl = (ctrl & ~0xC0) | (D_0032B508[env->std] << 6);
    ctrl = (ctrl & ~0xC) | (D_0032B518[env->mfd] << 2);
    if (env->rcyc) {
        ctrl |= 2;
        ctrl = (ctrl & ~0x300) | ((env->rcyc - 1) << 8);
    } else {
        ctrl &= ~2;
    }
    pcr = (env->express << 16) | env->notify;
    sqwc = (env->tqwc << 16) | env->sqwc;
    rbor = (u_int)env->rbadr;
    rbsr = env->rbmsk;
    *D_CTRL = ctrl;
    *D_PCR = pcr;
    *D_SQWC = sqwc;
    *D_RBOR = rbor;
    *D_RBSR = rbsr;
    D_004D0C00 = *env;
    return 0;
}

typedef char RuntimeDmaEnvironmentSize20[(sizeof(RuntimeDmaEnvironment) == 20) ? 1 : -1];
typedef char RuntimeDmaEnvironmentAlignment4[(__alignof__(RuntimeDmaEnvironment) == 4) ? 1 : -1];
