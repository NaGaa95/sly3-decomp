// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "ee_vu_upload_api.h"

extern unsigned int *D_0036BD38;
extern unsigned int *D_0036BD3C;
extern const unsigned char D_002C0250[];
extern const unsigned char D_002C45C0[];

/* TTE is bit 6 of the channel's 32-bit CHCR word. Corresponding
 * signed and unsigned integer views retain the same word representation.
 * Packet contents have separate VU source owners; these are address inputs. */
void func_001CB540(void)
{
    *(int *)D_0036BD38 |= 0x40;
    func_00293920(0);
    func_0029FD20(D_0036BD38, D_002C0250);
    func_0029FDE8(D_0036BD38, 0, 0);
    *(int *)D_0036BD38 &= ~0x40;
}

void func_001CB5B0(void)
{
    *(int *)D_0036BD3C |= 0x40;
    func_00293920(0);
    func_0029FD20(D_0036BD3C, D_002C45C0);
    func_0029FDE8(D_0036BD3C, 0, 0);
    *(int *)D_0036BD3C &= ~0x40;
}
