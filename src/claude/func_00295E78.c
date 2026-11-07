// Sly 2 counterpart: _request_call (decomp src/lib/_request_call.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -fno-strict-aliasing -G0
// SLY3_ASM: gnu-reorder-db
typedef struct Q { int tid; int active; int x8; struct SD *start; struct SD *end; } Q;
typedef struct SD {
    int x0, x4, x8;
    int xc;   /* 0x0C */
    int x10, x14, x18;
    int x1c, x20, x24, x28, x2c, x30, x34;
    int x38;
    struct SD *link; /* 0x3C */
    Q *base;  /* 0x40 */
} SD;
typedef struct {
    int x0, x4, x8, xc;
    int x10, x14, x18, x1c, x20, x24, x28, x2c, x30;
    SD *sd;   /* 0x34 */
} Req;
void func_002940F8(int);
void func_00295E78(Req *r)
{
    SD *sd = r->sd;
    Q *q = sd->base;
    if (q->start == 0)
        q->start = sd;
    else
        q->end->link = sd;
    q->end = sd;
    {
        int a = r->x14, c = r->x1c;
        sd->x20 = a;
        sd->x1c = c;
    }
    sd->x24 = r->x20;
    sd->xc = r->x24;
    sd->x28 = r->x28;
    sd->x2c = r->x2c;
    sd->x30 = r->x30;
    sd->x34 = r->x10;
    if (q->tid >= 0 && q->active == 0)
        func_002940F8(q->tid);
}
