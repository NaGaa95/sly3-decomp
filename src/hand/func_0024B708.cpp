// Sly 2 reference: src/hand/SaveSprBuf__FPve.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef char *va_list;
#define va_start(ap, last) (ap = ((char *)__builtin_next_arg(last) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8)))
#define va_arg(ap, T) (*(T *)((ap += 8) - 8))
#define va_end(ap)
typedef unsigned long ulong;
struct SBE { int cb; ulong *pv; };
struct SPRBUF { ulong *aqw; char *pv; SBE a[8]; int c; int state; };
struct DMAC { int chcr; int pad[31]; int sadr; };
extern "C" {
extern int D_00349870;
extern SPRBUF D_00475280[2];
extern DMAC *D_0036BD44;
void func_0029FDE8(DMAC *pch, int a, int b) __asm__("func_0029FDE8");
void func_0029FD98(DMAC *pch) __asm__("func_0029FD98");
}

void SaveSprBuf(void *pv, ...) __asm__("func_0024B708");
void SaveSprBuf(void *pv, ...)
{
    SPRBUF *psb = &D_00475280[D_00349870];
    void *apv[8];
    int c = 0;
    int j;
    DMAC *pch;
    va_list ap;
    psb->state = 3;
    func_0029FDE8(D_0036BD44, 0, 0);
    va_start(ap, pv);
    while (pv) {
        apv[c++] = pv;
        pv = va_arg(ap, void *);
    }
    j = 0;
    for (c = psb->c - c; c < psb->c - 1; c++, j++)
        psb->a[c].pv[-2] = (ulong)(psb->a[c].cb >> 4) | ((ulong)1 << 28) | ((ulong)(int)apv[j] << 32);
    pch = D_0036BD44;
    psb->a[c].pv[-2] = (ulong)(psb->a[c].cb >> 4) | ((ulong)7 << 28) | ((ulong)(int)apv[j] << 32);
    {
        pch->chcr &= ~0x40;
        pch->sadr = ((int)psb->pv & 0x0FFFFFFF) | 0x80000000;
        func_0029FD98(pch);
    }
    psb = &D_00475280[1 - D_00349870];
    if (psb->state == 3)
        psb->state = 0;
    va_end(ap);
}
