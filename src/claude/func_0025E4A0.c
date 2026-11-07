// SLY3_CFLAGS: -Os -G0
// For entry n (< 9) of the table at 0x349B20: true if both counts found by func_0025E348 are equal and nonzero.
struct E { int a, b; };
extern struct E D_00349B20[];
void func_0025E348(struct E *pe, int *pc0, int *pc1, int x);
int func_0025E4A0(unsigned int n, int x)
{
    int c0, c1;
    if (n >= 9) {
        __asm__ __volatile__(""); /* zero-instruction: keeps the early-return jump as in the target */
        return 0;
    }
    c0 = 0;
    c1 = 0;
    func_0025E348(&D_00349B20[n], &c0, &c1, x);
    return c0 && c0 == c1;
}
