// Sly 2 reference: src/hand/func_00256AF0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
typedef struct B { char pad[0x10]; int *base; } B;
typedef struct O { char pad[0xC]; B *pb; int (*pfn)(int *); char h[0x10]; } O;
int *func_002BA540(void *, int *, int *);

void func_002BA638(O *p, int *px)
{
    int a[2];
    void *h = p->h;
    a[1] = px - p->pb->base;
    a[0] = p->pfn(px);
    func_002BA540(h, &a[0], &a[1]);
}
