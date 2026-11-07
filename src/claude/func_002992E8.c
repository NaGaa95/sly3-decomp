// Sly 2 counterpart: func_0023A668 (decomp src/lib/func_0023A668.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct Alarm {
    struct Alarm *next;
    int x4;
    int (*func)(int, int, int, void *);
    void *arg;
} Alarm;
extern Alarm * volatile D_004CF080;
int func_002992E8(int id, int a1, int a2, Alarm *p)
{
    int r = p->func(((int)p << 4) | (id & 0xFE) | 1, a1, a2, p->arg);
    if (r == 0) {
        Alarm *h = D_004CF080;
        D_004CF080 = p;
        p->next = h;
        p->x4 = 0;
        return -1;
    }
    return r;
}
