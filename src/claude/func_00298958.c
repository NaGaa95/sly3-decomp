// Sly 2 counterpart: SetNextComp (decomp src/lib/SetNextComp.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct TC {
    struct TC *next;    /* 0x00 */
    int x4;
    long x8;
    unsigned long base_count; /* 0x10 */
    unsigned long base_time;  /* 0x18 */
    unsigned long schedule;   /* 0x20 */
} TC;
typedef struct {
    char pad[0x18];
    TC *head;       /* 0x18 */
    int current;    /* 0x1C */
} TimerG;
extern TimerG D_0034B650;
void func_00298750(int);   /* SetT2_COMP */
void func_00298740(int);   /* SetT2_MODE */
#define T2_COUNT (*(volatile int *)0x10001000)
#define T2_MODE  (*(volatile int *)0x10001010)
void func_00298958(unsigned long now)
{
    TC *t;
    unsigned long a0, a1;
    unsigned int mode;

    t = D_0034B650.head;
    if (D_0034B650.current >= 0)
        return;
    mode = T2_MODE;
    if (t == 0) {
        func_00298750(0);
        func_00298740(mode & ~0x800);
        return;
    }
    a0 = t->schedule + t->base_count - t->base_time;
    t = t->next;
    while (t != 0) {
        a1 = t->schedule + t->base_count - t->base_time;
        if (a1 < a0 + 0x7333)
            a0 = a1;
        else
            break;
        t = t->next;
    }
    if ((long)(a0 - now) < 0x7333) {
        func_00298750(T2_COUNT + (int)((unsigned long)0x7333 >> ((mode & 3) * 4)));
        func_00298740(mode & ~0x800);
        return;
    }
    func_00298740(mode & ~0x800);
    func_00298750(a0 >> ((mode & 3) * 4));
}
