// SLY3_CFLAGS: -Os -G0 -ffast-math
// Switch the state of the object (previous state: cycle the selected entry; new state: queue the matching sound/animation
// requests on the entry's object); same routine as Sly 2 func_001AEAA8.
struct LO;
typedef struct { short d; short pad; void (*pfn)(struct LO *, int); } VTE;
struct LO { int x0, x4, x8; VTE *vt; };
typedef struct { short d; short pad; void (*pfn)(void *); } VTS;
struct T18 { int x0, x4, x8, xC, x10, x14, x18, x1C, x20; };
struct ENT { int k; int pad[7]; };
typedef struct E { int x0; struct ENT *x4; struct LO *x8; int xC, x10; int x14; struct T18 *x18; } E;
typedef struct S { int x0, x4, x8; VTS *vt; char pad[0x38 - 0x10]; int x38; E ae[1]; char pad2[0x1FC - 0x3C - 0x1C]; int x1FC; } S;
extern float D_00475140, D_00475144;
void func_00262450(struct LO *, int);
void func_00261580(struct LO *, int, float);
int func_00260758(struct LO *, int);
int func_001D2E70(S *s);
void func_001D2ED0(S *s, int st)
{
    E *pe;
    if (s->x1FC == st)
        return;
    pe = 0;
    if (s->x38 > 0)
        pe = &s->ae[s->x38 - 1];
    switch (s->x1FC) {
    case 5:
        if (pe) {
            if (++pe->x14 >= pe->x0)
                pe->x14 = 0;
        }
        break;
    case 6:
        if (pe) {
            if (--pe->x14 < 0)
                pe->x14 = pe->x0 - 1;
        }
        break;
    case 0:
    case 1:
    case 11:
        break;
    }
    s->x1FC = st;
    switch (st) {
    case 1:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            p->vt[53].pfn((struct LO *)((char *)p + p->vt[53].d), pe->x18->x0);
            func_00262450(pe->x8, pe->x18->xC);
            if (pe->x18->x20) {
                int v = func_001D2E70(s);
                if (!func_00260758(pe->x8, v))
                    func_00262450(pe->x8, v);
            }
        }
        break;
    case 3:
        if (pe && pe->x8)
            func_00262450(pe->x8, pe->x18->x14);
        break;
    case 4:
        if (pe && pe->x8)
            func_00262450(pe->x8, pe->x18->xC);
        break;
    case 2:
    case 8:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            p->vt[53].pfn((struct LO *)((char *)p + p->vt[53].d), pe->x18->x8);
            func_00262450(pe->x8, pe->x18->x14);
        }
        break;
    case 5:
        if (pe && pe->x8)
            func_00262450(pe->x8, pe->x18->x18);
        break;
    case 6:
        if (pe && pe->x8)
            func_00262450(pe->x8, pe->x18->x1C);
        break;
    case 11:
        if (pe && pe->x8)
            func_00262450(pe->x8, 0x3B7);
        break;
    case 9:
        if (pe && pe->x8)
            func_00262450(pe->x8, 0x3B8);
        break;
    case 10:
        if (pe && pe->x8) {
            switch (*(int *)((char *)pe->x4 + (pe->x14 << 5))) {
            case 0x77:
                func_00262450(pe->x8, 0x3B9);
                func_00262450(pe->x8, 0x37C);
                func_00261580(pe->x8, 0x37C, D_00475144);
                break;
            case 0x78:
                func_00262450(pe->x8, 0x3BA);
                func_00262450(pe->x8, 0x37C);
                func_00261580(pe->x8, 0x37C, D_00475140);
                break;
            case 0x4E:
                func_00262450(pe->x8, 0x3BB);
                break;
            }
        }
        break;
    case 7:
        if (pe && pe->x8) {
            struct LO *p = pe->x8;
            p->vt[53].pfn((struct LO *)((char *)p + p->vt[53].d), pe->x18->x4);
            func_00262450(pe->x8, pe->x18->x10);
            if (pe->x18->x20) {
                int v = func_001D2E70(s);
                if (!func_00260758(pe->x8, v))
                    func_00262450(pe->x8, v);
            }
        }
        break;
    case 0:
        s->vt[11].pfn((char *)s + s->vt[11].d);
        break;
    }
}
