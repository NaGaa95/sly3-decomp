// Sly 2 counterpart: sceIpuRestartDMA (decomp src/lib/sceIpuRestartDMA.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    unsigned int d4madr;
    unsigned int d4tadr;
    unsigned int d4qwc;
    unsigned int d4chcr;
    unsigned int d3madr;
    unsigned int d3qwc;
    unsigned int d3chcr;
    unsigned int ipubp;
} sceIpuDmaEnv;
void func_002B32C8(unsigned int);
void func_002B3340(unsigned int);
void func_002B34A0(sceIpuDmaEnv *env)
{
    int bp = env->ipubp & 0x7F;
    int fifo = ((env->ipubp >> 16) & 3) + ((env->ipubp >> 8) & 0xF);
    unsigned int madr = env->d4madr - fifo * 16;
    unsigned int qwc = env->d4qwc + fifo;

    if (env->d3madr && env->d3qwc) {
        *(volatile unsigned int *)0x1000B010 = env->d3madr;
        *(volatile unsigned int *)0x1000B020 = env->d3qwc;
        func_002B32C8(env->d3chcr | 0x100);
    }
    while (*(volatile int *)0x10002010 < 0);
    *(volatile unsigned int *)0x10002000 = bp;
    while (*(volatile int *)0x10002010 < 0);
    if (madr && qwc) {
        *(volatile unsigned int *)0x1000B410 = madr;
        *(volatile unsigned int *)0x1000B430 = env->d4tadr;
        *(volatile unsigned int *)0x1000B420 = qwc;
        func_002B3340(env->d4chcr | 0x100);
    }
}
