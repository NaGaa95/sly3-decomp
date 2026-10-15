// Sly 2 reference: src/hand/func_00160A98.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/vifs.h"
#include "../P2/gifs.h"
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct FR {
    int cqwGifs;     /* 0x00 */
    QW *aqwGifs;     /* 0x04 */
    int pad8[2];
    int cqwVifs;     /* 0x10 */
    QW *aqwVifs;     /* 0x14 */
    int pad18[2];
    int cqw20;       /* 0x20 */
    QW *aqw24;       /* 0x24 */
    int pad28[3];
    DL dl34;         /* 0x34 */
    DL dl40;         /* 0x40 */
};
extern FR *D_0036C328;
extern VIFS D_0036C308;
extern GIFS D_0036C2E0;
extern DL D_0036C658;
extern DL D_0036C668;
extern int D_0036C684;
void FinalizeFrameVifs(VIFS *pvifs, int *pcqw, QW **paqw) __asm__("func_00182D88");
void FinalizeFrameGifs(GIFS *pgifs, int *pcqw, QW **paqw) __asm__("func_00182E68");
extern "C" void func_0011AF40(DL *pdl) __asm__("func_0011AF40");
extern "C" void func_002936C0(int sid) __asm__("func_002936C0");
extern "C" void func_00182EE0() __asm__("func_00182EE0");
extern "C" void func_00182EE0()
{
    FinalizeFrameVifs(&D_0036C308, &D_0036C328->cqwVifs, &D_0036C328->aqwVifs);
    FinalizeFrameGifs(&D_0036C2E0, &D_0036C328->cqwGifs, &D_0036C328->aqwGifs);
    D_0036C328->cqw20 = D_0036C328->aqwVifs + D_0036C328->cqwVifs - D_0036C328->aqw24;
    D_0036C328->dl34 = D_0036C658;
    func_0011AF40(&D_0036C658);
    D_0036C328->dl40 = D_0036C668;
    func_0011AF40(&D_0036C668);
    D_0036C328 = 0;
    func_002936C0(D_0036C684);
}
