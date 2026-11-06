// SLY3_CFLAGS: -Os -G0 -ffast-math -fno-exceptions -fno-rtti
// func_002340B8: build the 256-entry shading palette (CLUT) of a lit object and queue its GS upload. Three light colours
// (rows at +0xA0, converted by func_0011F6E8) and their gains (+0x90) are folded into three RGBA words; the palette index
// bits select none / light 1 / light 0 / light 2 (n & 0x81) and the remaining bits a 0..1 ramp that scales the light alpha.
// With an upload source (pbs) the TEX0 word at +0xD0 is rebuilt first; the palette is sent as a 0x40 quadword DMA ref.
// The two short "nop" loops are wait delays (the in/out operand keeps the counter alive).
#include "../P2/gifs.h"

struct VEC3 { float x, y, z; };
struct CLR { uint n; };
struct OBJ {
    char pad[0x90];
    float gain[3];
    float pad9C;
    float color[3][4];
    ulong tex0;
};
extern uint D_0036BD40;
extern int D_00349700[];
extern "C" {
void func_0011F6E8(const float *, VEC3 *);
int func_00196C18(void *, int);
void func_00196D28(int, int, int, int, int, int, GIFS *);
void func_00195760(uint, QW *);
void func_002340B8(OBJ *p, void *pbs);
}

static inline void Delay(int n)
{
    int i = n;
    while (i != -1) {
        i--;
        __asm__("nop\n\tnop\n\tnop\n\tnop" : "+r"(i));
    }
}

static inline void StoreColor(CLR *outColor, float *outAlpha, float gain, const VEC3 &v)
{
    uint rgb = (uint)(int)v.x | ((uint)(int)v.y << 8) | ((uint)(int)v.z << 16);
    float alpha = gain * 0.003921569f;
    outColor->n = rgb;
    *outAlpha = alpha;
}

static inline void ClearClr(CLR *pc) { pc->n = 0; }

static inline void SetClr(CLR *pc, float g, float gA, uint rgb)
{
    float h = gA * 128.0f;
    pc->n = rgb | ((uint)(int)(g * h) << 24);
}

void func_002340B8(OBJ *p, void *pbs)
{
    if (!pbs && !(p->tex0 & (0x3FFFL << 37)))
        return;
    {
        float ag[3];
        CLR argb[3];
        VEC3 v;
        int i;
        Delay(2);
        for (i = 0; i < 3; i++) {
            func_0011F6E8(p->color[i], &v);
            StoreColor(&argb[i], &ag[i], p->gain[i], v);
        }
        CLR aclr[256];
        Delay(0xFF);
        {
            CLR *pc = aclr;
            int n = 0;
            int k;
            for (k = 0; k < 0x100; k += 0x20) {
                int j;
                for (j = 0; j < 4; j++) {
                    int m;
                    for (m = 0; m < 8; m++) {
                        int a = (n & 0x7F) - 1;
                        float g0, g;
                        if (!(a > -1))
                            a = 0;
                        g0 = a * 0.007936508f;
                        g = (g0 > 0.0f) ? g0 : 0.0f;
                        switch (n & 0x81) {
                        case 0x81:
                            SetClr(pc++, g, ag[2], argb[2].n);
                            break;
                        case 0x80:
                            SetClr(pc++, g, ag[0], argb[0].n);
                            break;
                        case 1:
                            SetClr(pc++, g, ag[1], argb[1].n);
                            break;
                        case 0:
                            ClearClr(pc++);
                            break;
                        }
                        n++;
                    }
                    n += D_00349700[j];
                }
            }
        }
        if (pbs)
            p->tex0 = ((ulong)func_00196C18(pbs, 4) << 37) | 0x2000000001B00000L;
        GIFS dmas;
        QW aqw[0x80];
        QW *x;
        dmas.AllocStatic(0x80, aqw);
        dmas.AddDmaCnt();
        func_00196D28((int)((p->tex0 >> 37) & 0x3FFF), 1, 0, 0x10, 0x10, 0x40, &dmas);
        dmas.AddDmaRefs(0x40, (QW *)aclr);
        dmas.AddPrimPack(0, 1, 14);
        dmas.PackAD(0x3F, 0);
        dmas.PackAD(0x61, 0);
        dmas.AddPrimEnd();
        dmas.AddDmaEnd();
        dmas.Detach(0, &x);
        func_00195760(D_0036BD40, x);
    }
}
