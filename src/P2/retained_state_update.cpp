// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Provisional state view, bound to the original concrete constructors/tables.
struct VTE { short d; short p; void (*pfn)(void *); };
struct P {
    char pad[0xC];
    VTE *pvt;
    float f10;
    char pad2[0x44 - 0x14];
    int n44;
    float f48;
    int x4C;
    int x50;
    int x54;
    int x58;
    unsigned short f5C;
    unsigned short n5E;
};
extern "C" void func_00245320(P *, int, int);

#define VCALL(p, n) ((p)->pvt[n].pfn((char *)(p) + (p)->pvt[n].d))
#define ICALL(p, n) (((int (*)(void *))(p)->pvt[n].pfn)((char *)(p) + (p)->pvt[n].d))

struct Lock {
    P *p;
    Lock(P *pp) { p = pp; VCALL(p, 1); }
    ~Lock() { VCALL(p, 2); }
};

extern "C" void func_00245748(P *p)
{
    // Keep the receiver retained through every callback, including early exits.
    Lock l(p);
    unsigned short fl;
    if (p->f5C & 0x200)
        VCALL(p, 16);
    else {
        p->x50 = 0;
        p->f48 = p->f10;
    }
    fl = p->f5C;
    if (fl & 1) {
        // Sly3 queries slot8 and updates the flags before invoking slot9.
        if (ICALL(p, 8) == 1)
            func_00245320(p, 0x400, 0x400);
        VCALL(p, 9);
    } else if (p->n44) {
        if (fl & 8) {
            VCALL(p, 10);
            p->n44 = 0;
            func_00245320(p, 0x1DFF, 0);
        } else {
            if (fl & 0x1C00)
                VCALL(p, 14);
            if (p->n5E)
                return;
            if (p->f5C & 0x1F0) {
                VCALL(p, 13);
                func_00245320(p, 0x1F0, 0);
            }
            fl = p->f5C;
            if (fl & 2) {
                VCALL(p, 11);
                func_00245320(p, 2, 0);
            } else if (fl & 4) {
                VCALL(p, 12);
                func_00245320(p, 4, 0);
            }
        }
    } else if (!p->n5E && !(fl & 0x200)) {
        func_00245320(p, 0x1FFF, 0);
    }
}
