// SLY3_CFLAGS: -Os -G0 -ffast-math
// Map the current record (0x11C0-byte entries starting at D_0036E740) to its menu slot, remember the slot and
// return the key assigned to it.
extern int D_0046F568;
extern char D_0036E740[];
extern int D_003899E8;
extern int D_00345F90[];
int func_001A9260(void *record);
void func_001D5178(int *out)
{
    int slot = func_001A9260(D_0036E740 + D_0046F568 * 0x11C0);
    D_003899E8 = slot;
    *out = D_00345F90[slot];
}
