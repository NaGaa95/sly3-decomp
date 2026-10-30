// SLY3_CFLAGS: -Os -G0
// EE hardware intrinsics preserve COP0 operations; C expresses control flow.
// Sly 2 reference: /home/claude/decomp src/hand/func_0014CFE0.c.
struct CLOCK {
    int fEnabled;
    float t;
    float rDt;
    float rDtPrev;
    char pad[8];
    float af[10];
    char pad2[0x48 - 0x40];
    unsigned long tick;
    unsigned long tickLast;
    int hi;
};
extern struct CLOCK g_clock;
unsigned long func_001655B0(struct CLOCK *p);
void func_001653E0(struct CLOCK *p);
void func_00165358(void)
{
    unsigned long c[2];
    unsigned int i;
    __asm__ volatile ("mfc0 %0, $9" : "=r"(c[0]));
    g_clock.tickLast = c[0];
    g_clock.tick = func_001655B0(&g_clock);
    for (i = 0; i < 10; i++) g_clock.af[i] = 1.0f;
    g_clock.rDt = 1.0f;
    g_clock.rDtPrev = 1.0f;
    func_001653E0(&g_clock);
}
