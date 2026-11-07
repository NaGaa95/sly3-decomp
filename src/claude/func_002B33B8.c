// Sly 2 counterpart: sceIpuStopDMA (decomp src/lib/sceIpuStopDMA.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    unsigned int d4madr, d4tadr, d4qwc, d4chcr;
    unsigned int d3madr, d3qwc, d3chcr;
    unsigned int ipubp, ipuctrl;
} sceIpuDmaEnv;
void func_002B32C8(unsigned int v);
void func_002B3340(unsigned int v);
#define R(a) (*(volatile unsigned int *)(a))
void func_002B33B8(sceIpuDmaEnv *env)
{
    func_002B3340(1);
    env->d4madr = R(0x1000B410);
    env->d4tadr = R(0x1000B430);
    env->d4qwc = R(0x1000B420);
    env->d4chcr = R(0x1000B400);
    while (R(0x10002010) & 0xF0)
        ;
    func_002B32C8(0);
    env->d3madr = R(0x1000B010);
    env->d3qwc = R(0x1000B020);
    env->d3chcr = R(0x1000B000);
    env->ipubp = R(0x10002020);
    env->ipuctrl = R(0x10002010);
}
