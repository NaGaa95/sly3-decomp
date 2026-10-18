// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/gifs.h"
#include "../P2/vifs.h"
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct FR {
    int cqwGifs;       /* 0x00 */
    QW *aqwGifs;       /* 0x04 */
    QW *aqwGifsBuf;    /* 0x08 */
    int cqwGifsBuf;    /* 0x0C */
    int cqwVifs;       /* 0x10 */
    QW *aqwVifs;       /* 0x14 */
    QW *aqwVifsBuf;    /* 0x18 */
    int cqwVifsBuf;    /* 0x1C */
    int cqw20;         /* 0x20 */
    QW *aqw24;         /* 0x24 */
    int n28;           /* 0x28 */
    int n2C;           /* 0x2C */
    int n30;           /* 0x30 */
    DL dl34;           /* 0x34 */
    DL dl40;           /* 0x40 */
    int n4C;           /* 0x4C */
    int n50;           /* 0x50 */
    int n54;           /* 0x54 */
    char rest[0x190 - 0x58];
};
extern FR *D_0036C328;
extern FR D_0036C330[2];
extern unsigned int D_0036C67C;
extern int D_00467B00;
extern int D_0036C688;
extern int D_00479284;
extern GIFS D_0036C2E0;
extern VIFS D_0036C308;
extern QW D_0036E2A0[];
extern "C" void func_001F1430(int phase);
extern "C" int func_002936E0(int semaphore);
extern "C" void func_001834F8(FR *frame);

extern "C" void func_00182C68(void)
{
    if(!D_00467B00)
        func_001F1430(3);
    func_002936E0(D_0036C688);
    D_0036C328 = &D_0036C330[D_0036C67C++];
    if(D_0036C67C >= 2)
        D_0036C67C = 0;
    func_001834F8(D_0036C328);
    D_0036C328->n4C = D_00479284;
    D_0036C328->n30 = 0xF;
    D_0036C328->n2C = 0;
    D_0036C328->aqw24 = 0;
    D_0036C328->n54 = D_0036C328->n50;
    D_0036C2E0.AllocStatic(D_0036C328->cqwGifsBuf, D_0036C328->aqwGifsBuf);
    D_0036C308.AllocStatic(D_0036C328->cqwVifsBuf, D_0036C328->aqwVifsBuf);
    D_0036C2E0.AddDmaRefs(10, D_0036E2A0);
    D_0036C2E0.AddDmaCnt();
}
