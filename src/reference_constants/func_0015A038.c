// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct VTE {
    short d;
    short pad;
    void (*pfn)(void *);
};
struct LO {
    char pad[0xC];
    struct VTE *vt;
};
struct X14 {
    struct LO *plo;
};
struct P {
    char pad[0xC];
    struct VTE *vt;
    char pad1[0x14 - 0x10];
    struct X14 *px14;
    char pad2[0x130 - 0x18];
    int state;
    float tState;
    char pad3[0x140 - 0x138];
    void *resource140;
};
typedef char StateReceiverPrefix144[(sizeof(struct P) == 0x144) ? 1 : -1];
struct CLOCK {
    char pad[0x40];
    float time40;
};
extern struct CLOCK D_0036BB98;
extern struct P *D_0036B330;
extern char D_00474FF0[];
extern char D_00475480[];
void func_00248598(void *p, int a, int b);
void func_00165548(struct CLOCK *p, int a, float g);
void func_001A93C8(void *p, int key, int option);
void func_001A9420(void *p, int key, int option);
int func_001C8610(struct P *p);
void func_0011AF60(void *p, struct X14 *px);
void func_00138B88(void *p, float g);
void func_0015A038(struct P *p, int state) {
    if (state == p->state) return;
    switch (p->state) {
        case -1: D_0036B330 = p;
        func_00248598(D_00474FF0, 2, 0);
        func_00165548(&D_0036BB98, 8, 0.0f);
        func_001A93C8(D_00475480, -1, 0);
        p->vt[8].pfn((char *)p + p->vt[8].d);
        if (!func_001C8610(p)) {
            struct LO *plo;
            func_0011AF60(D_00475480 + 0x3DF8, p->px14);
            plo = p->px14->plo;
            plo->vt[25].pfn((char *)plo + plo->vt[25].d);
        }
        break;
        case 3: if (p->resource140) func_00138B88(p->resource140, 1.0f);
        break;
    }
    p->state = state;
    p->tState = D_0036BB98.time40;
    switch (state) {
        case -1: D_0036B330 = 0;
        func_00165548(&D_0036BB98, 8, 1.0f);
        func_00248598(D_00474FF0, 2, 1);
        func_001A9420(D_00475480, -1, 0);
        p->vt[9].pfn((char *)p + p->vt[9].d);
        break;
        case 3: if (p->resource140) func_00138B88(p->resource140, 0.0f);
        break;
    }
}
