// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of a two-body constraint set (based on Sly 2 func_001F3980): run the base update, tick the active
// elements, copy the two bodies' positions into the shared record, clear the contact accumulators when a body is in mode
// 1 or 2 and send virtual slot 74, then finish the base update and process the elements that are not flagged.
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct VTE { short d; short p; void (*pfn)(void *); };
struct E { char pad[0x14]; int active; ulong fl; char pad2[0xD0 - 0x20]; };
struct Q { char pad[0x98]; short h98; char pad2[0xB0 - 0x9A]; qword vB0; char padC0[0xF0 - 0xC0]; int aF0[3]; };
struct R { char pad[0x60]; qword v60; qword v70; };
struct P { char pad[0xC]; struct VTE *pvt; char pad2[0x48 - 0x10]; struct Q *p58; struct Q *p5C; char pad3[0xD0 - 0x50]; int nE0; struct E *aE4; struct R *pE8; };
extern struct { float t; float dt; } D_0036BB98;
void func_0023C878(struct P *);
void func_002403F0(struct E *, float);
int func_0028F048(int);
void func_0028CA78(struct P *);
void func_0023C840(struct E *);
static inline void Clear(int *a)
{
    a[2] = 0;
    a[1] = 0;
    a[0] = 0;
}
void func_0023C970(struct P *p)
{
    int i;
    struct E *pe;
    func_0023C878(p);
    for (i = 0; i < p->nE0; i++) {
        pe = &p->aE4[i];
        if (pe->active) func_002403F0(pe, D_0036BB98.dt);
    }
    if (p->pE8) {
        if (p->p58) p->pE8->v60 = p->p58->vB0;
        if (p->p5C) p->pE8->v70 = p->p5C->vB0;
        if ((unsigned short)(p->p58->h98 - 1) < 2 || p->p5C->h98 == 1 || p->p5C->h98 == 2) {
            if (func_0028F048(p->p58->h98)) {
                Clear(p->p58->aF0);
            }
            if (func_0028F048(p->p5C->h98)) {
                Clear(p->p5C->aF0);
            }
            p->pvt[74].pfn((char *)p + p->pvt[74].d);
        }
    }
    func_0028CA78(p);
    for (i = 0; i < p->nE0; i++) {
        pe = &p->aE4[i];
        if (!(pe->fl & 0x80000)) func_0023C840(pe);
    }
}
