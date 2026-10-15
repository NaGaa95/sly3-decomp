// Construct the inherited receiver with its explicit owner pointer and mode, initialize six unit float controls, and apply original global resource-state disable conditions.
// Reference algorithm: src/hand/func_001FC190.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct P { char pad[0xC]; void *pvt; char pad2[0x60 - 0x10]; void *owner; char pad3[0x70 - 0x64]; float a[6]; char pad4[0x3B8 - 0x88]; int n3B8; };
struct G { char pad[0x58]; int n58; char pad2[0x160 - 0x5C]; float a[3]; };
extern struct G D_00474FF0;
extern char D_00365C30[];
struct P *func_00244BC8(struct P *);
void func_00245320(struct P *, int, int);
int func_00246EF0(struct G *, void *);
void func_00244C28(struct P *);
struct P *func_00246040(struct P *p, void *owner, int m)
{
    int i;
    struct G *pg;
    func_00244BC8(p);
    p->owner = owner;
    p->pvt = D_00365C30;
    p->n3B8 = m;
    for (i = 0; i < 6; i++) p->a[i] = 1.0f;
    func_00245320(p, 0x801, 0x801);
    pg = &D_00474FF0;
    if (*(pg->a + func_00246EF0(pg, p->owner)) == 0.0f) func_00244C28(p);
    if (pg->n58) func_00244C28(p);
    return p;
}
