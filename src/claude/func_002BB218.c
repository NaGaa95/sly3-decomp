// Reference: Sly 2 src/hand/func_00257C18.c; target Sly 3 0x002BB218.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
typedef struct N { int x0; int x4; union { int w; struct { unsigned prevpg : 4; unsigned prev : 11; unsigned p1 : 1; unsigned nextpg : 4; unsigned next : 11; unsigned mark : 1; } f; } u; int pad; } N;
extern char *D_004D2A18[];
extern char D_004D2AD8[];
extern N *D_0036AE00, *D_0036AE0C;
extern int D_0036B138;
void func_002B3B90(N *);
void func_0011E1F0(void *, void *);

static inline N *Ptr(unsigned pg, unsigned idx)
{
    if (pg == 0 && idx == 0)
        return 0;
    return (N *)(D_004D2A18[pg] + idx * 0x10);
}

static inline N *Next(N *p)
{
    return Ptr(p->u.f.nextpg, p->u.f.next);
}

void func_002BB218(void)
{
    N *p;
    int zero = 0;
    for (p = D_0036AE00; p && p != D_0036AE0C; p = Next(p)) {
        if ((p->u.w < zero) != D_0036B138)
            p->u.f.mark = D_0036B138;
    }
    while (p) {
        N *cur = p;
        N *next = Next(cur);
        int m;
        p = next;
        m = D_0036B138;
        if ((cur->u.w < zero) != m) {
            func_002B3B90(cur);
            func_0011E1F0(D_004D2AD8, cur);
        }
    }
}
