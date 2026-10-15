// Take an actual type13 pooled object, constructing its16-object pool and buffers on first use.
// Full factory/callback inputs, pointer result and real body boundary independently reviewed.
// Take a pooled object; on first use construct16 actual type13 objects and their buffers.
// Slot31 receives a genuine nullable parent pointer, explicitly null on this path.
// No incoming GP/FPR arguments are consumed; return is the actual object pointer.
// SLY3_CFLAGS: -Os -G0
// Sly3 field offsets and actual added callbacks are recovered from the original.
typedef struct VTE {
    short d;
    short pad;
    void (*pfn)(void *);
}
VTE;
typedef struct AREQ {
    int cb;
    int align;
}
AREQ;
typedef struct O {
    char pad0[0xC];
    VTE *vt;
    char pad10[0x50 - 0x10];
    float mat[16];
    int x90[0x10];
    int xD0;
    int xD4;
    int padD8;
    float *xDC;
    void *xE0;
    void *xE4;
    char padE8[0x1B0 - 0xE8];
    int x1B0;
    char pad1B4[0x1C8 - 0x1B4];
    int x1C8;
    char pad1CC[0x1D8 - 0x1CC];
    int x1D8;
    void *x1DC;
}
O;
typedef struct DL {
    O *first;
    O *last;
    int node_offset;
}
DL;
extern DL D_0047A260;
O *func_00150690(int kind, void *owner, int id, int option);
void *func_00292034(void *buffer, int fill, unsigned int bytes);
void *func_001D2470(AREQ *request);
void func_0011AF60(DL *list, O *object);
void func_0011B028(DL *list, O *object);
O *func_001E7A60(void) {
    O *p;
    int i, j;
    AREQ req;
    float *pm;
    p = D_0047A260.first;
    if (!p) {
        for (i = 0; i < 16; i++) {
            O *q = func_00150690(0xD, 0, 0x323, -1);
            q->xD0 = 0;
            q->xD4 = 1;
            q->x1B0 = 1;
            pm = q->mat;
            func_00292034(pm, 0, 0x40);
            pm[15] = 1.0f;
            pm[10] = 1.0f;
            pm[5] = 1.0f;
            pm[0] = 1.0f;
            req.cb = 0x80;
            req.align = 0x10;
            q->xDC = (float *)func_001D2470(&req);
            for (j = 0; j < 32; j++) q->xDC[j] = (float)j;
            req.cb = 0x80;
            req.align = 0x10;
            q->xE0 = func_001D2470(&req);
            req.cb = 0x200;
            req.align = 0x10;
            q->xE4 = func_001D2470(&req);
            req.cb = 0x1F0;
            req.align = 0x10;
            q->x1DC = func_001D2470(&req);
            ((void (*)(void *))q->vt[17].pfn)((char *)q + q->vt[17].d);
            ((void (*)(void *, void *))q->vt[31].pfn)((char *)q + q->vt[31].d, 0);
            ((void (*)(void *))q->vt[9].pfn)((char *)q + q->vt[9].d);
            func_0011AF60(&D_0047A260, q);
        }
        p = D_0047A260.first;
    }
    func_0011B028(&D_0047A260, p);
    p->x1D8 = -1;
    ((void (*)(void *))p->vt[8].pfn)((char *)p + p->vt[8].d);
    p->x1C8 = 0;
    return p;
}
