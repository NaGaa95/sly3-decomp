// SLY3_CFLAGS: -Os -G0
/* Message handler: state transitions + option flags (rodata 0x31FA40..0x31FA7F: id/-1 pair lists). */
struct PAIR { int n; int x; };
struct Q { char pad[0x50]; int grf; };
struct MSG { void *p0; void *p4; int n8; };
struct MSG12 { int x0; void *p4; struct Q *pq; };
struct O { char pad[0x1190]; int x1190; };
struct OB { char pad[0x1B4]; int f1B4; };
struct P { struct OB *po; int st; float g8; void *pc; int x10; float g14; void *pd; char pad[0x28 - 0x1C]; int x28, x2C, x30, x34; };
int func_00139918(void *);
void func_0013ABC8(struct P *, int);
void func_00138C70(void *, struct OB *, int);
void func_00138CC8(void *, struct OB *, int, const struct PAIR *);
void func_001B0650(struct OB *);
void func_0013A770(struct P *p, int msg, struct MSG *pm)
{
    static const struct PAIR a0[3] = { { 0x30, -1 }, { 0x2B, -1 }, { 0x2D, -1 } };
    static const struct PAIR a1[3] = { { 0x31, -1 }, { 0x2A, -1 }, { 0x2C, -1 } };
    static const struct PAIR a2[2] = { { 0x38, -1 }, { 0x39, -1 } };
    switch (msg) {
    case 12: {
        struct MSG12 *pm12 = (struct MSG12 *)pm;
        struct Q *pq = pm12->pq;
        if (p->st != -1 && (pq->grf & 1) && pm12->p4 == p->po && p->pc && func_00139918(p->pc))
            func_0013ABC8(p, 2);
        break;
    }
    case 5:
        if ((void *)pm == p->pd)
            func_0013ABC8(p, -1);
        break;
    case 10:
        if (pm->p0 == p->pd) {
            switch (pm->n8) {
            case 0x18C:
                if (p->st == 1)
                    func_00138C70(pm->p0, p->po, ((struct O *)p->po)->x1190);
                break;
            case 0x18D:
                if (p->st == 1)
                    func_00138CC8(pm->p0, p->po, 3, a0);
                break;
            case 0x18E:
                if (p->st == 1)
                    func_00138CC8(pm->p0, p->po, 3, a1);
                break;
            case 0x18F:
                if (p->st == 1)
                    func_00138CC8(pm->p0, p->po, 2, a2);
                break;
            case 0x2A2:
                p->x28 = 1;
                break;
            case 0x40:
                p->po->f1B4 = 1;
                break;
            case 0x41:
                p->po->f1B4 = 0;
                break;
            case 0x2A0:
                p->x2C = 1;
                break;
            case 0x2A1:
                p->x30 = 1;
                break;
            case 0x2A3:
                p->x34 = 0;
                break;
            case 0x2A4:
                p->x34 = 1;
                break;
            case 0xFB:
                func_001B0650(p->po);
                break;
            }
        }
        break;
    }
}
