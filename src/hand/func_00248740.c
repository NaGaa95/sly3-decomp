// Finish all remaining descriptor updates, notify the selected attachment, stop its reference, destroy all seven attachments, and clear the collection and duration fields.
// Reference algorithm: src/hand/func_001FE738.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short p; void (*pfn)(void *); };
struct VT { struct VTE a[3]; };
struct X { char pad[0xC]; struct VT *pvt; };
struct A { int a, b; };
struct E { char pad[0x54]; int c; struct A *ae; };
struct Y { char pad[0x60]; struct E *pe; };
struct Ref { struct Y *px; };
struct P { char pad[0x210]; struct Ref r; char pad2[0x22C - 0x204]; struct X *ap[7]; int n244; int n248; float g24C; };
void func_002480C8(struct P *, struct A *);
void func_00239CE8(void *, int);
void func_00244CA8(struct Y *, float);
void func_002BF360(struct Ref *, void *);
void func_00292034(void *, int, int);
static inline void Stop(struct Ref *pr)
{
    if (pr && pr->px) {
        func_00244CA8(pr->px, 0.0f);
        func_002BF360(pr, 0);
    }
}
void func_00248740(struct P *p)
{
    int i;
    struct E *pe;
    if (!p->r.px) return;
    pe = p->r.px->pe;
    while (p->n244 < pe->c) {
        func_002480C8(p, &pe->ae[p->n244]);
        p->n244++;
    }
    if (p->ap[5]) func_00239CE8(p->ap[5], 0x6E2);
    Stop(&p->r);
    p->n244 = 0;
    p->n248 = 0;
    p->g24C = 0.0f;
    for (i = 0; i < 7; i++) {
        struct X *px = p->ap[i];
        if (px) px->pvt->a[2].pfn((char *)px + px->pvt->a[2].d);
    }
    func_00292034(p->ap, 0, 0x1C);
}
