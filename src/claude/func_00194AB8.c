// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Microcode blob 0x2C1D00..0x2C2630 has no symbol in symbol_addrs.txt; addressed relative to the nearest one
   (D_002C1CF0). The second declaration is the same symbol under another C name so gcc does not derive the end
   address from the start address. */
extern char D_002C1CF0[];
extern char D_002C1CF0_b[] __asm__("D_002C1CF0");
void func_00182D60(void *pvifs, void *pvStart, void *pvEnd);
void func_00194AB8(void *a, void *b, void *pvifs)
{
    func_00182D60(pvifs, D_002C1CF0 + 0x10 /* 0x2C1D00 */, D_002C1CF0_b + 0x940 /* 0x2C2630 */);
}
